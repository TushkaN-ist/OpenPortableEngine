#include "UserMain.h"

#include <Frame/Frame.h>
#include <Input/Input.h>
#include <Graphic/Render.h>
#include <Platform/PlatformApp.h>
#include <Platform/FPS.h>
#include <Math/Util.h>
#include <Math/Quaternion.h>

#include <ModelPMD.h>
#include <TexturePC.h>
#include <IO/IOFile.hpp>

#define SIMPLEBMP_OPENGL
#include <simplebmp.h>

char* _APP_NAME = "Open Portable Engine";

namespace UserBehaviour{
	void _UserMain(int argc, char **argv){
		char path[255];
		std::map<unsigned short,unsigned char> materialsMap;
		int i=1;
		while(i<=24){
			sprintf(path,"meshdata\\track%u.PMD",i);
			printf("%s\n",path);
			PMDHeader* pmd = (PMDHeader*)LoadGameFile(path);
			
			PolygonData *polygons;
			int c = pmd->offsetsTableSize[1]/sizeof(PolygonData);
			pmd->SetOffsetPoint(1,polygons);

			while(c--){
				unsigned short id = (polygons->materialID<<8)|polygons->materialPower;
				if (materialsMap.find(id) == materialsMap.end()) {
					printf("%X\n",id);
					materialsMap.insert(std::make_pair(id,polygons->materialID));
				// not found
				}
				polygons++;
			}
			free(pmd);
			i++;
		}
	}
	void UserMain(int argc, char **argv){
		PMDHeader* pmd = (PMDHeader*)LoadGameFile("meshdata\\car5.PMD");
        Lod &lod = *pmd->GetLodPoint();
		OCTree *tree;
		Vertex *bounds;
		CollisionBlock *collision;
		AIPath *paths;
		unsigned short *block25, *block24;
		unsigned int size31 = pmd->offsetsTableSize[31]/48;
		if (pmd->type == TypePMD::Track){
			tree = pmd->TrackGetOCTree();
			bounds = pmd->TrackGetBounds();
			collision = pmd->TrackGetCollision();//work in progress
			pmd->SetOffsetPoint(25,block25);
			pmd->SetOffsetPoint(24,block24);
			paths = pmd->TrackGetAIPaths();
		}

    	timeBeginPeriod(1);
		if (OGL::TestInit()){
			Frame *frame = Frame::Create(640,480,Frame::Style::Closing);
			//frame->SetTitle("MainFrame");
			Input &input = *frame->GetInput();
			OGL *graphic = OGL::Create(frame);
			OGL::SetVerticalSync(false);

			GL::Shader vert(GL::ShaderType::Vertex, 
			"#version 130\n varying vec4 v_color; varying vec2 v_texcoord; void main() { gl_Position = ftransform(); v_color = gl_Color.rgba; v_texcoord = gl_MultiTexCoord0.st; }");
			GL::Shader frag(GL::ShaderType::Fragment,
			"#version 130\nuniform sampler2D tex; varying vec4 v_color; varying vec2 v_texcoord; void main() { gl_FragColor = v_color * texture(tex, v_texcoord); if (gl_FragColor.a<0.5) discard; }");
			GL::Program program(vert, frag);

			//GL::VertexBuffer vbo(((char*)(pmdPack->vertexs))+pmdPack->meshs[0].vertPoint,pmdPack->meshs[0].vertexCount*12,GL::BufferUsage::StaticDraw);//(vertices, sizeof(vertices), GL::BufferUsage::StaticDraw);
			//GL::VertexBuffer vbo((char*)mesh.vertPoint,mesh.vertexCount * 16,GL::BufferUsage::StaticDraw);//(vertices, sizeof(vertices), GL::BufferUsage::StaticDraw);
			//GL::VertexBuffer vboInd((char*)mesh.polysPoint,pmdPack->meshs[0].polysCount*2, GL::BufferUsage::StaticDraw);
			//GL::VertexArray vao;

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_VERTEX_ATTRIB_ARRAY_ENABLED);

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CW);

			lod.LoadTextures("Unpacked\\graphics24\\","trackset00");

			glActiveTexture(GL_TEXTURE0);
			program.SetUniform(program.GetUniform("tex"), 0);

			GL::Mat4 proj = GL::Mat4::Perspective(GL::Deg2Rad(60), 640.f/480.f, 100.f, 500000.f).Scale(-1,1,1);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glLoadMatrixf(proj.m);
			glMatrixMode(GL_MODELVIEW);

			GL::Quaternion rotate;
			GL::Mat4 CameraFirstPos, cameraPosition, cameraRotation;
			switch(pmd->type){
				case TypePMD::Track:{
					cameraPosition.Translate(GL::Vec3(0, 0, 20000));
				}break;
				case TypePMD::Car:{
					cameraPosition.Translate(GL::Vec3(0, 0, 500));
				}break;
			}
			//vao.BindAttribute(program.GetAttribute("position"), vbo, GL::Type::Float, 4, 0, 0);
			//vao.BindElements(vboInd);
			FPS *fps = FPS::Create(30);
			printf("Set FPS:%i\n",fps->GetTargetFPS());
			GL::Vec3 rot(125, 45, 0);
			GL::Vec3 rotSpd(0, 0, 0);

			int p = 0;
			glEnable(GL_POINT_SIZE);
			glEnable(GL_LINE_WIDTH);
			glPointSize(5);
			glLineWidth(2);
			GL::Mat4 move = GL::Mat4::Identity();

			while ( fps->Update() && frame->Update())
			{
				if (input.Down(KEYCODE::KC_ESCAPE)){
					frame->Close();
					break;
				}
				rotSpd = rotSpd * (0.9 + 0.1 * fps->GetDelta());
				if (input.Press(KEYCODE::KC_RIGHT))
					rotSpd.x -= 45.f * fps->GetDelta();
				if (input.Press(KEYCODE::KC_LEFT))
					rotSpd.x += 45.f * fps->GetDelta();
				if (input.Press(KEYCODE::KC_UP))
					rotSpd.y -= 45.f * fps->GetDelta();
				if (input.Press(KEYCODE::KC_DOWN))
					rotSpd.y += 45.f * fps->GetDelta();
					rot += rotSpd;
				rotate = GL::Quaternion::FromDeg(GL::Vec3(rot.y, rot.x, 0));
				if (input.Press(KEYCODE::KC_PGDOWN))
					cameraPosition.Translate(GL::Vec3(0, 0, 1500 * fps->GetDelta()));
				if (input.Press(KEYCODE::KC_PGUP))
					cameraPosition.Translate(GL::Vec3(0, 0, -1500 * fps->GetDelta()));
					
				if (input.Down(KEYCODE::KC_Q))
					p=(p+1)%255;
				if (input.Down(KEYCODE::KC_A) && p>0)
					p--;
				Vertex v = pmd->type == TypePMD::Track?*(paths[0].pointVertex+p):Vertex();
				CameraFirstPos = GL::Mat4::TRS(GL::Vec3(v.x,v.y,v.z),rotate,GL::Vec3(1,1,1));
				GL::Mat4 matrixCameraResult = (CameraFirstPos * cameraPosition).Inverse();

				graphic->MakeCurrent(frame);
				OGL::ClearColor();
				OGL::Clear();
				glLoadMatrixf(matrixCameraResult.m);

				switch(pmd->type){
					case TypePMD::Track:{
						lod.Draw(0, tree, bounds, block25, nullptr);
						paths->Draw();
					}break;
					case TypePMD::Car:{
						if (input.Down(KEYCODE::KC_SPACE))
							(lod.GetLodMesh()+10)->isVisible = !(lod.GetLodMesh()+10)->isVisible;
						lod.Draw();
					}break;
				}
				//OGL::DrawArrays(vao, Primitive::Points, 0, mesh.vertexCount);
				//OGL::DrawArrays(vao, Primitive::Points, 0, pmdPack->header->offsetsTableSize[]);
				graphic->SwapBuffers();
				
			}
			lod.FreeTextures();

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_VERTEX_ATTRIB_ARRAY_ENABLED);

			glDisable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			delete fps;
			delete graphic;
			delete frame;
		}
    	timeEndPeriod(1);
		free(pmd);
	}
}