/*
 * =====================================================================================
 *
 *       Filename:  xSpaceGroup2D.cpp
 *
 *    Description:  wallpaper groups
 *
 *        Version:  1.0
 *        Created:  07/10/2014 15:51:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Pablo Colapinto (), gmail -> wolftype
 *   Organization:  
 *
 * =====================================================================================
 */


#include "vsr_app.h"   
#include "form/vsr_fold.h"
#include "form/vsr_group.h"
#include "form/vsr_simplex.h"
#include "form/vsr_field.h"

using namespace vsr;
using namespace vsr::cga;

template<int N>
void Drw( const Simplex<N>& s, float dist=1.0, bool bOrtho=false){

  using Vec = NEVec<3>;

  auto proj = s.project(dist);

  glNormal3f(0,0,1);
  glColor3f(1,0,0);
  for (auto& i : s.edges){
    gfx::Glyph::Line( proj[i.a], proj[i.b] );
  }

  glColor4f(0,0,1,.2);
  for (auto& i : s.faces){
    gfx::Glyph::Triangle( proj[i.a], proj[i.b], proj[i.c] );
  }

}

struct MyApp : App {    
   
  Pnt mouse;
  Lin ray;

  float time;
  float amt,pNum,ratio,div,numDraw,iter;
  bool bPin, bGlideA, bGlideB,bReset,bSnap,bDrawMotif;

  Point pa = PT(0,0,0);
  Point pb = PT(1,0,0);
  Point pc = PT(0,1,0);
  Point pd = PT(0,-1,0);


  void setup(){
      bindGLV();
      gui(amt,"amt",-100,100);
      gui(bReset,"reset");
      gui(bDrawMotif,"bDrawMotif");
      gui(bSnap,"snap");
      gui(pNum,"pnum",1,6);
      gui(ratio,"ratio",0,2);
      gui(div,"div",1,10);
      gui(bPin,"pin");          ///< pin or spin
      gui(bGlideA,"ga");        ///< glide
      gui(bGlideB, "gb");
      gui(iter,"iter",0,200);
      amt = .5;
      ratio = 1.0;
      bPin = true;
      pNum = 2;
      iter = 1;

      objectController.attach(&pa);
      objectController.attach(&pb);
      objectController.attach(&pc);
      objectController.attach(&pd);

      mColor.set(1,1,1);
  }
  

    virtual void onDraw(){ 
        
      mouse = calcMouse3D();
      time++;

      //Template on motif type
      SpaceGroup2D<Vec> sg(pNum,ratio,bPin,(int)div,bGlideA,bGlideB);

      
      vector<Pair> motif;
      motif.push_back(pa^pb); motif.push_back(pa^pc); motif.push_back(pa^pd);// motif.push_back

      auto single = sg.apply(motif,3,3); 
      if (bSnap){                
        for (auto& i : single){
          auto sa =  round::split(i,true);
          auto sb =  round::split(i,false);

          if ( round::sqd(sa, pa) < .03 ) pa = round::null( pa + (sa-pa) *.05);
          else if ( round::sqd(sb, pa) < .03 ) pa = round::null( pa + (sb-pa)*.05);
          if ( round::sqd(sa, pb) < .03   ) pb = round::null( pb + (sa-pb) *.05);
          else if ( round::sqd(sb, pb) < .03 ) pb = round::null( pb + (sb-pb)*.05);
          if ( round::sqd(sa, pc) < .03 ) pc = round::null( pc + (sa-pc) *.05);
          else if ( round::sqd(sb, pc) < .03 ) pc = round::null( pc + (sb-pc)*.05);
          if ( round::sqd(sa, pd) < .03 ) pd = round::null( pd + (sa-pd) *.05);
          else if ( round::sqd(sb, pd) < .03 ) pd = round::null( pd + (sb-pd)*.05);

        }
      }
      auto res = sg.apply(motif,iter,iter);

      for (auto& i : res){
        Draw(i,0,0,0);
      }

      if (bDrawMotif){
        Draw( round::dls(pa,.1),0,0,0,.5  );
        Draw( round::dls(pb,.1),0,0,0,.5  );
        Draw( round::dls(pc,.1),0,0,0,.5 );
        Draw( round::dls(pd,.1),0,0,0,.5 );
      }
      
      if(bReset){
        pa = PT(0,0,0);
        pb = PT(1,0,0);
        pc = PT(0,1,0);
        pd = PT(0,-1,0);
      }

      cout << "num mirror ops: " << sg.ops.size() << endl; 
      cout << "num spin ops: " << sg.sops.size() << endl; 
      cout << "num glide ops: " << sg.gops.size() << endl; 
      cout << "num res: " << single.size() << endl;
      
  }
   

  
};



int main(){
  MyApp app;
  app.start();
  return 0;                             
}
