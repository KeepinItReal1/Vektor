# ObjektinisProgramavimas

# Naudojimosi instrukcija

## Spartos analizė:
Atlikta 100 bandymų push_back'inant std::pow(10,8) int'ų.

Optimization flag'as | Vektor time   | Vector time | Difference |
-------------------- | ------------- | --------    |------------|
None                 | 2.76035s      | 1.89973s    | -31,17%    |
O1                   | 2.74534s      | 1.84049s    | -32,95%    |
O2                   | 2.74189s      | 1.83942s    | -32,91     |
O3                   | 2.74132s      | 1.85509s    | -32,33%    |
O4                   | 2.74304s      | 1.8402s     | -32,91     |



## Kas buvo sunkiausia:
```cpp
       iterator insert( const_iterator pos, const value_type& value ){//klaida
            const difference_type temp = pos-cbegin();//atstumas nuo pradzios cia neveikia
            if(end_==end_of_range ){
                createNewArray(std::max(1,static_cast<int>(capacity_)));//capacity_ size_t neina lygint su int...      
            }
            size_t m=0;
            for(auto k=end();k>begin()+temp;k--){//
                allocator_.construct(end_-m,*(end_-1-m));
                m++;
            }
            allocator_.construct(begin_ + temp, value);
            size_++;
            end_=A+size_;
            return begin()+temp;
        }
 ```
 ## Naudinga:
 
 ```cpp
        //copy assignment operator
        vektor& operator= (const vektor& x){
            this->size_=x.size_;
            this->capacity_=x.capacity_;
            this->allocator_=x.allocator_;//"The container preserves its current allocator, except if the allocator traits indicate that x's allocator should propagate."
            this->A=(allocator_.allocate(x.size_));
            this->begin_= A;
            this->end_=A+size_;
            this->end_of_range=A+capacity_;
            int k=0;auto i=x.begin_;
            while(i!=x.end_){
                allocator_construct(this->begin_+k,1,*i);
                k++;i++;
            }
            return *this;
        }

 ```
 


