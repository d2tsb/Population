
#include "Vector.h"

void test()
{
  Vector<std::string> a({"hello ", "what's", " up. "});
  a.print();
  Vector<std::string> b = {"hello ", "what's", " down. "};
  b.print();
  a = b; 
  a.print(); 
  Vector<unsigned> c; 
  c.push_back(1);
  c.push_back(2);
  c.push_back(4);
  c.push_back(3);
  c.print(); 
  std::cout << "capacity of c: " << c.getCapacity() << std::endl; 
  std::cout << "size of c: " << c.getSize() << std::endl; 

  c.reserve (3000);
  std::cout << "capacity of c after reservation of 3000: " << c.getCapacity() << std::endl; 
  c.pop_back();
  c.pop_back();
  c.pop_back();
  c.pop_back();
  c.pop_back();
  std::cout << "capacity of c after pop_back(): " << c.getCapacity() << std::endl; 
  std::cout << "and its size of c after pop_back(): " << c.getSize() << std::endl; 
  c.resize(60);
  std::cout << "capacity of c after resize(60): " << c.getCapacity() << std::endl; 
  std::cout << "size of c after resize(60): " << c.getSize() << std::endl; 
  b.resize(10);
  b.fill("hallo");
  b.print(); 
  b.fill("xyz");
  std::cout << "size of b after resize(10): " << b.getSize() << std::endl; 
  std::cout << b[9] << std::endl ;

  Vector<Vector<std::string>> d( {{"I'm the first sentence."}, {"hello", "i'm ", " the ", " second ", "sentence"}});
  d[0].print(); 
  d[1].print(); 
  
  d.resize(9);
  std::cout << "capacity of d: " << d.getCapacity() << std::endl; 
  d.fill(Vector<std::string> ({"hi, i'm the filler. ", "i fill the booth"}));
  d[4].print();
  d[8] = Vector<std::string> ({ "i m", " the 8th element. "});
  d[8].print(); 
  d[8].fill("lol");
  d[8].print(); 
  for ( unsigned i = 0; i<2000; i++)
  {
    d.push_back({"bla", "bla", "bla", "bla"});
  }
  std::cout << "capacity of d: " << d.getCapacity() << std::endl; 
}


int main ()
{
  test(); 

}

