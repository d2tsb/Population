#include "defines.h"
#include <utility>

#define illegalArgumentException 89 
#define illegalStateExcetion 90
#define CERR(x) std::cerr << x << std::endl; 

#define DEFAULTSTEPSIZE 1000
template <typename T>
class Vector 
{

  unsigned capacity__ = 0;  //>= 0
  unsigned size__ = 0;  //>= 0   
  //a size of 0 contains no elements, a size of 1 contains 1 elements, and a size of N contains n elements.
  T * data__ = NULL; 
  unsigned stepSize = DEFAULTSTEPSIZE; // >= 20
  void copyFromAToB(T*A, T*B, unsigned amount) noexcept
  {
    for (unsigned i = 0; i < amount; i++)
    {
      B[i] = A[i];
    }
  }
  void shrink(unsigned size)
  {
        if ( data__ == NULL)
        {
          try
          {
            data__ = new T[size + stepSize];
            this->capacity__ = size + stepSize; 
          }
          catch(const std::exception& e)
          {
            std::cerr << e.what() << '\n';
          }
          return; 
        }
        T * temp = NULL;
        try
        {
        //shrink capacity to size + stepSize 
          temp = new T[size + stepSize]; 
        //only copy the elements in new range
          copyFromAToB(data__, temp, size);
          delete [] data__;
          data__ = temp; 
          this->capacity__ = size+stepSize;  
        }
        catch(const std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }

  }
  void reallocate()
  {
    data__ = new T[capacity__]; 
  }
  T* copy(){
    T * temp; 
    try
    {
      /* code */
      temp = new T[capacity__]; 
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    
    copyFromAToB(data__, temp, size__);
    return temp; 
  }
  public:
    void reserve (unsigned capacity) //increase capacity
    {
      
      //capacity can't be smaller than 1
      //since capacity__ is atleast 0
      if ( capacity > capacity__)
      {//reserve a new amount of memory
        if ( data__ == NULL)
        {
          data__ = new T[capacity];
          capacity__ = capacity; 
          return; 
        } //in strict regards - it is actually code duplication the copy() function
        // implemented above could be used to handle it all.
        T * temp = NULL;
        try
        {
          temp = new T[capacity]; 
          copyFromAToB(data__, temp, size__); //does nothing if size__ == 0
          delete [] data__;
          data__ = temp; 
          this->capacity__ = capacity;  
          /* code */
        }
        catch(const std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }
      }
      //does nothing - capacity remains unchanged if capacity is smaller than 
      //this->capacity__. 
    }
    void resize(unsigned size)
    {
      //size can't be smaller than 0
      
      if ( size > capacity__)
      {//reserve a new amount of memory
        reserve ( size);
      }
      else if (size + stepSize < capacity__ ){
        shrink( size ); //else keep capacity the same
      }
      //write new elements with the default constructor of T
      
      //if size * 2 smaller than capacity - make smaller
      const int size_conv = (int)size__;
      for ( int i = size - 1; i >= size_conv; i--) 
      {//does nothing if size__ and size are the same or size__ > size.
        //the smallest size__ can have is 0
          data__[i] = T(); 
      }
      this->size__ = size; 
      //the object on the heap stay alive as long no pushback or happens to 
      //overwrite the elements of type T

    } //increase size
    Vector getDeepCopy()
    {
      Vector v(*this);  //reserve another vector with the same capacity
      v.reallocate(); 
      copyFromAToB ( data__, v.data__, size__);
      v.size__ = size__; 
      v.capacity__ = capacity__; 
      return v; 
      
    }
    void push_back(T obj)
    {
      
      if ( size__ + 1 >= capacity__)
      {
        //allocate more
        reserve(capacity__ + stepSize);
        ++size__;
        data__[size__-1] = obj; 
      }
      else {
        ++size__;
        data__[size__-1] = obj; 
      }

    }
    void pop_back()
    {
      //it does nothing to the object in data__[size__] the only thing 
      //can happen is that it gets overwritten by a pushback
      //or the shrink of the data__ causes data destruction.
      //this requires T's Destructor to be suddely implemented.
      if ( size__ )
      {
        --size__;
      }
      if ( size__ % stepSize == 0)
      {
        shrink(size__); //'shrinks' the capacity to size__ + stepSize
      }
   }
    void setStepSize(unsigned NStepSize = 20)
    {
      if ( NStepSize < 20)
      {
        CERR("In Vector.setStepSize(): stepSize has to be greater than 20. Given was: " << NStepSize)
        throw illegalArgumentException; 
      }
      else {
        this->stepSize = NStepSize; 
        shrink(stepSize); 
      }

    }
    T first()
    {
      if (size__)
        return data__[0];
      CERR("In Vector.first(): Vector seems to be empty().")
      throw illegalStateExcetion; 

    }
    void last()
    {
      if (size__)
        return data__[size__-1];
      CERR("In Vector.last(): Vector seems to be empty().")
      throw illegalStateExcetion; 
    }
    unsigned getSize()
    {
      return size__; 
    }
    unsigned getCapacity()
    {
      return capacity__; 
    }
    void fill(T element)
    {
      for ( unsigned i = 0; i<size__; i++)
      {
        this->data__[i] = element; 
      }
    }

    void print()
    {
      for ( unsigned i = 0; i < size__; i++)
      {
        std::cout << data__[i] << " "; 
      }
      std::cout << std::endl; 
    }

    Vector(std::initializer_list<T> l)
    {
      shrink(l.size());
      unsigned i = 0; 
      for ( auto & value : l) 
      {
        this->data__[i] = value;
        i++;
      }
      this->size__ = l.size(); 
    }
    Vector(unsigned capacity, bool initialize = false)
    {
      if ( !capacity )
      {
        CERR("In Vector.Vector(unsigned, bool): capacity needs to be > 0.")
        throw illegalArgumentException;
      }
      stepSize = DEFAULTSTEPSIZE; //sure for sure
      reserve (2*stepSize);

      if (initialize)
      {
        resize(2*stepSize);
      }
    }
    Vector()
    {
      shrink(0);
    }
    Vector(Vector&other)
    {
      this->capacity__ = other.capacity__; 
      this->size__ = other.size__; 
      this->stepSize = other.stepSize; 
      this->data__ = other.copy(); 
    }
    Vector& operator = (Vector &other)
    {
      Vector temp(other);
      std::swap(temp.capacity__, this->capacity__);
      std::swap(temp.size__, this->size__);
      std::swap(temp.stepSize, this->stepSize);
      std::swap(temp.data__, this->data__);
      return *this; 
    }

    ~Vector()
    {
      delete [] data__; 
    }


    T operator [] (unsigned i)
    {
      if ( i < size__)
      {
        return data__[i];
      }
      return T(); 
    }
};
