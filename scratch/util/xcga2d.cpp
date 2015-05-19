#include "space/vsr_cga2D_types.h"  


using namespace vsr;
using namespace vsr::cga2D;

int main(){
	
	
	auto a = round::point(1,0);
	         
	auto b = round::point(0,1);
	         
	auto c = round::point(-1,0);  


	(a ^ b ^ c).print();
	auto cir = a^b^c;
	
	 cir.print();  
   
 	
	printf("direction\n");
	Drv().print();   
	printf("tangent\n");
	Tnv().print();
	printf("bivector\n");  
	Biv().print();  
	                  
 
	printf("line (grade 3)\n");
	Lin().print();  
	printf("dualLine (grade 1)\n");
	Dll().print();
	printf("dualFlatPoint\n");
	(Pnt() ^ Inf()).dual().print();
  printf("circle (3-blade)\n");
	Cir().print();  	
	printf("pair (2-blade)\n");
	Par().print();
	printf("pseudocalar (4-blade)\n");
	Sph().print();  

	printf("rotor (s + biv)\n");
	auto r = gen::rot( Biv(1) ); r.print();
	
	printf("translator (s + drv)\n");
	auto t = gen::trs( Drv(1,1) ); t.print();    
	
	printf("motor (s + biv + drv )\n");
	( t * r).print();
		
	printf("transversor (s + tnv)\n");
	gen::trv( Tnv(1,1) ).print();  
	
	printf("boost (s + par)\n");
	gen::bst( Par(1,1) ).print();
	                                  
	( Lin() * Sph() ).print();  
	
	Par( Tnv()).sp( gen::trs( Drv(1,0) ) ).print();

  printf("dual pair\n");
  (op::dual( Par() ).print() );
	
	// ( Pnt() * Sph() ).bprint();
	// 
	// Par tp = b ^ c; 
	// //(tp+.1).vprint();
	// auto bst = gen::bst( tp ); 
	// bst.vprint();
	// bst.bprint();             
	// 
	// // Sca s = (Vec(1,0)*Vec(.5,1)).get<0>();
	// // s.vprint(); 
	// 
	// auto ra =  gen::ratio( Vec(1,0), Vec(0,1) );
	//     ra.vprint(); 
	// ra.bprint();   
	
	// //( Tnv(1,0) + 1 ).bprint(); 
	// for (int i = 0; i < 100; ++i){
	// 	float t = 1.0 * i/100;
	//     Pnt np = a.sp( gen::bst( Pair( b, c ) * t ) ); 
	// 	
	// 	np /= np.get< 4 >();
	//    // np.vprint();
	// }  
	
}
