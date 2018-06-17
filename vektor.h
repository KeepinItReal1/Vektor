#ifndef VEKTOR_H
#define VEKTOR_H

#include <windows.h>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <math.h>
// #include <stdexcept>

template <class T, class Alloc = std::allocator<T>> class vektor{

    public:
    	typedef T 																value_type;
    	typedef Alloc 															allocator_type;
    	typedef value_type&														reference;
    	typedef const value_type& 												const_reference;
    	typedef typename std::allocator_traits<allocator_type>::pointer    		pointer;
    	typedef typename std::allocator_traits<allocator_type>::const_pointer	const_pointer;
    	typedef __gnu_cxx::__normal_iterator<pointer, vektor> 					iterator;
      	typedef __gnu_cxx::__normal_iterator<const_pointer, vektor>				const_iterator;
      	typedef std::reverse_iterator<iterator>									reverse_iterator;
      	typedef std::reverse_iterator<const_iterator>							const_reverse_iterator;
      	typedef typename __gnu_cxx::iterator_traits<iterator>::difference_type	difference_type;
      	typedef size_t 															size_type;


 
        //c-tors
        
        //default-empty
    	explicit vektor ( const allocator_type& alloc = allocator_type() ) :
    		size_(0),
    		capacity_(0),
    		allocator_(alloc),
    		A(nullptr),
    		begin_(nullptr),
    		end_(nullptr),
    		end_of_range(nullptr)
			{
				std::cout<<"Vektor default-empty c-tor."<<std::endl;
			};

        //fill
		explicit vektor ( size_type count, const_reference value, const allocator_type& alloc = allocator_type() ):
    		size_(count),
    		capacity_(count),
    		allocator_(alloc),
    		A(allocator_.allocate(count)),
    		begin_(A),
    		end_(A+size_),
    		end_of_range(A+capacity_)
			{
				std::cout<<"Vektor fill c-tor."<<std::endl;
				allocator_construct(begin_ , count, value);
			};

        //range
    	template < class InputIt, typename = std::_RequireInputIter<InputIt> > 
    	vektor( InputIt first, InputIt last, const allocator_type& alloc = allocator_type() )://paziureti del greicio last - first ar std::distance(first,last);
            size_(last - first),
            capacity_(last - first),
            allocator_(alloc),
            A(allocator_.allocate(last - first)),
            begin_(A),
            end_(A+size_),
            end_of_range(A+capacity_)
            {
                std::cout<<"Vektor range c-tor."<<std::endl;
                // std::copy(first,last, begin_ );
                auto i=first;
                while(i!=last){
                    allocator_construct(begin_,1,A[i]);//konstruos nuo begin_ 1 elementa su A[i] reiksme
                    i++;
                }
                
            };

        //copy nr 1
        vektor(const vektor& x):
            size_(x.size_),
            capacity_(x.capacity_),
            A(allocator_.allocate(x.size_)),
            begin_(A),
            end_(A+size_),
            end_of_range(A+capacity_)
            {
                std::cout<<"Vektor 1st copy c-tor."<<std::endl;
                auto i=x.begin_;
                int k=0;
                while(i!=x.end_){
                    allocator_construct(begin_ + k,1,*i);//konstruos nuo begin_ 1 elementa su A[i] reiksme
                    i++;k++;    
                }

            };

        //copy nr 2
        vektor( const vektor& x, const Alloc& alloc ):
            size_(x.size_),
            capacity_(x.capacity_),
            allocator_(alloc),
            A(allocator_.allocate(x.size_)),
            begin_(A),
            end_(A+size_),
            end_of_range(A+capacity_)
            {
                std::cout<<"Vektor 2nd copy c-tor."<<std::endl;
                auto i=x.begin_;
                int k=0;
                while(i!=x.end_){
                    allocator_construct(begin_ + k ,1,x.A[i]);//konstruos nuo begin_ 1 elementa su A[i] reiksme
                    i++;k++;
                }

            };

    	//move c-tor nr 1
    	vektor( vektor&& x ):
            size_(x.size_),
            capacity_(x.capacity_),
            allocator_(x.allocator_),
            A(allocator_.allocate(x.size_)),
            begin_(A),
            end_(A+size_),
            end_of_range(A+capacity_)
            {
                x=nullptr;
            };
    	
    	//move nr 2
    	vektor( vektor&& x, const Alloc& alloc ):
            size_(x.size_),
            capacity_(x.capacity_),
            allocator_(alloc),
            A(allocator_.allocate(x.size_)),
            begin_(A),
            end_(A+size_),
            end_of_range(A+capacity_)
        {
            A = std::move(x);
        };
        
    	//initializer_list c-tor
    	vektor( std::initializer_list<value_type> init, const allocator_type& alloc = allocator_type() ):
            size_(init.size()),
            capacity_(init.size()),
            allocator_(alloc),
            A(allocator_.allocate(init.size())),
            begin_(A),
            end_(A+size_),
            end_of_range(A+capacity_)    
            {
                std::cout<<"Vektor initializer_list c-tor."<<std::endl;
                int k=0;
                for(auto i : init){
                    allocator_construct(begin_ + k,1, i);
                    k++;
                }
            };

        //d-tor
        ~vektor(){
            for(size_t i = 0 ; i < capacity_; i++){ 
                allocator_.destroy(A +i);             //tam    reik funkcijos
            }
            allocator_.deallocate(A, capacity_);
            A=nullptr;
            end_=nullptr;
            begin_=nullptr;
            end_of_range=nullptr;
        }

        //other member functions
        allocator_type get_allocator() const noexcept{
            return allocator_;
        }

        void assign (size_type count, const_reference value){//test
            for(size_t i = 0 ; i < capacity_; i++){ 
                allocator_.destroy(A +i);             //tam    reik funkcijos
            }
            allocator_construct(begin_ , count, value);

            size_  = count;
            begin_ = A;
            end_ = A + size_;
        }

        template < class InputIt, typename = std::_RequireInputIter<InputIt> > //test
        void assign( InputIt first, InputIt last ){
            for(size_t i = 0 ; i < capacity_; i++){ 
                allocator_.destroy(A +i);             //tam    reik funkcijos
            }
                auto i=first;
                while(i!=last){
                    allocator_construct(begin_,1,A[i]);//konstruos nuo begin_ 1 elementa su A[i] reiksme
                    i++;
                }

            size_ = last - first;
            begin_ = A;
            end_ = A + size_;

        }

        void assign( std::initializer_list<T> ilist ){//test , nuo c++11
            for(size_t i = 0 ; i < capacity_; i++){ 
                allocator_.destroy(A +i);             //tam    reik funkcijos
            }
            int k=0;
            for(auto i : ilist){
                allocator_construct(begin_ + k,1, i);
                k++;
            }

            size_ = ilist.size();
            begin_ = A;
            end_ = A + size_;
        }
        



        //iterators
        inline iterator begin(){return iterator(begin_);};
        inline iterator end(){return iterator(end_);};

        inline const_iterator begin() const {return const_iterator(begin_);};
        inline const_iterator end() const {return const_iterator(end_);};

        inline reverse_iterator rbegin(){return reverse_iterator( end() );};
        inline reverse_iterator rend(){return reverse_iterator( begin() );};

        inline const_reverse_iterator rbegin() const{return const_reverse_iterator( end() );};
        inline const_reverse_iterator rend() const {return const_reverse_iterator( begin() );};

        inline const_iterator cbegin() const {return const_iterator(begin_);};
        inline const_iterator cend() const {return const_iterator(end_);};


        inline const_reverse_iterator crbegin() const {return const_reverse_iterator( cend() );};
        inline const_reverse_iterator crend() const {return const_reverse_iterator( cbegin() );};

        //Capacity

        bool empty() const noexcept{
            if( begin()==end() )
                return true;
            else return false;
        }

        size_type size() const{return size_;};

        size_type max_size() const noexcept{//kazkodel neatima 1
            auto m= sizeof(T);
            if(sizeof(size_t)==4){
                return pow(2,32)/m - 1;
            }
            else return pow(2,64)/m - 1;

        }

        void reserve( size_type new_cap ){//++
            if(new_cap>max_size()){throw std::length_error("Reserve more than max_size()");}
            else{
                if(new_cap>capacity_){
                    pointer B = allocator_.allocate(new_cap);
                    for(size_t i = 0 ; i < capacity_; i++){ //construct until copied
                        allocator_.construct( B + i, A[i] );
                        allocator_.destroy(A + i);                  
                    }

                    allocator_.deallocate(A, capacity_);
                    A = B;
                    capacity_=new_cap;
                    begin_=A;
                    end_=A+size_;
                    end_of_range=A+capacity_;
                }
            }
        }
        
        size_type capacity() const{return capacity_;};

        void shrink_to_fit(){
            if(capacity_>size_){
                pointer B = allocator_.allocate(size_);
                    for(size_t i = 0 ; i < size_; i++){ //construct until copied
                        allocator_.construct( B + i, A[i] );
                        allocator_.destroy(A + i);           
                    }
                    allocator_.deallocate(A, capacity_);
                    A = B;
                    capacity_=size_;
                    begin_=A;
                    end_=A+size_;
                    end_of_range=A+capacity_;
            }
        }


        //Element access (references)
        reference operator[](size_t n){
            return *(begin_ + n);
        }

        const_reference operator[] (size_t n) const{
            return *(cbegin() + n);
        }

        reference at(size_t n){
            if(n>=size_){
                throw std::out_of_range("Accessing element out_of_range at");
            }
            else return *(begin_ + n);
        }

        const_reference at(size_t n) const{
            if(n>=size_){
                throw std::out_of_range("Accessing element out_of_range at");
            }
            else return *(cbegin() + n);
        }

        reference front(){
            return *begin_;
        }

        const_reference front() const{
            return *cbegin();
        }

        reference back(){
            return *end_;
        }

        const_reference back() const {
            return *cend();
        }

        pointer data() noexcept{
            return A;
        }

        const pointer data() const noexcept{//const 
            return A;
        }


        //operators
        //not too sure del return type
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

        //move assignment operator
        vektor& operator= (vektor&& x){
            this->size_=x.size_;
            this->capacity_=x.capacity_;
            this->allocator_=x.allocator_;//"The container preserves its current allocator, except if the allocator traits indicate that x's allocator should propagate."
            this->A=(allocator_.allocate(x.size_));
            this->begin_= A;
            this->end_=A+size_;
            this->end_of_range=A+capacity_;
            this->A=std::move(x);   
            return *this;
        }

        //initializer list
        vektor& operator= (std::initializer_list<value_type> il){
            this->size_=il.size();
            this->capacity_=il.size();
            this->A=(allocator_.allocate(il.size()));
            this->begin_= A;
            this->end_=A+size_;
            this->end_of_range=A+capacity_;
            for(auto i : il){
                allocator_construct(this->begin_+i,1,i);
            }           
            return *this;
        }

        
        bool operator== (const vektor<value_type>& rhs){
            if(this->size_ == rhs.size_){
                size_t i=0;
                while(this->A[i] == rhs.A[i]){
                    i++;
                }
                if(i == rhs.size_)
                return 1;
            }
            else return 0;
        }

        
        bool operator!= (const vektor<value_type>& rhs){
            return this->A == rhs.A ? 0 : 1;
        }

        
        bool operator< (const vektor<value_type>& rhs){
            return std::lexicographical_compare(this->begin_, this->end_, rhs.begin_, rhs.end_) == 1 ?  1 : 0 ;
        }

        
        bool operator<= (const vektor<value_type>& rhs){
            return (this->A < rhs.A || this->A == rhs.A) ? 1 : 0; 
        }

        
        bool operator>  (const vektor<value_type>& rhs){
            return this->A < rhs.A ? 1 : 0;
        }

        
        bool operator>= (const vektor<value_type>& rhs){
            return this->A <= rhs.A ? 0 : 1; 
        }


        //functions
        template<class OutputIterator, class Size>
        void allocator_construct(OutputIterator first, Size n, const_reference val){
            int i=0;
            while(i<n){
                allocator_.construct(first +i,val);
                i++;
            }
        }


        //modifiers

        void clear() noexcept{
            for(size_t i = 0 ; i < size_; i++){ 
                allocator_.destroy(A +i);             
            }
            end_=begin_;
        }

        iterator insert( const_iterator pos, const value_type& value ){//klaida
            if(size_==capacity_){
                if(capacity_!=0){
                    reserve(capacity_*2);  
                }
                else reserve(capacity_+1);
            }
            const difference_type temp = pos-cbegin();//atstumas nuo pradzios
            //turiu insertint begin_+temp value, ten buvusia reiksme su visom pastumt i deisne

            size_t m=0;
            for(auto k=end();k>=begin()+temp;k--){//
                allocator_.construct(begin_+size_-m,*(k-1));
                m++;
            }
            allocator_.destroy(begin_+temp);    
            allocator_.construct(begin_ + temp, value);//cia neveikia
            size_++;end_++;
            return begin()+temp;//nes return pos neveik
        }

        // iterator insert( const_iterator pos, T&& value ){
        //     if(size_==capacity_){
        //         if(capacity_!=0){
        //             reserve(capacity_*2);  
        //         }
        //         else reserve(capacity_+1);
        //     }




        // }

        // iterator insert( const_iterator pos, size_type count, const T& value ){
        //     if(size_==capacity_){
        //         if(capacity_!=0){
        //             reserve(capacity_*2);  
        //         }
        //         else reserve(capacity_+1);
        //     }

        // }

        // template< class InputIt >
        // iterator insert( const_iterator pos, InputIt first, InputIt last ){
        //     if(size_==capacity_){
        //         if(capacity_!=0){
        //             reserve(capacity_*2);  
        //         }
        //         else reserve(capacity_+1);
        //     }

        // }

        // iterator insert( const_iterator pos, std::initializer_list<T> ilist ){
        //     if(size_==capacity_){
        //         if(capacity_!=0){
        //             reserve(capacity_*2);  
        //         }
        //         else reserve(capacity_+1);
        //     }

        // }


        void push_back(value_type elem){// reikia exception del pasiekto max_size
            if(size_ == capacity_){
                if(capacity_!=0){
                    createNewArray(capacity_ * 2);
                }
                else{
                    createNewArray(1);
                }
            }    
                allocator_.construct(begin_ + size_, elem);
                size_++;
                end_++;
        }

        iterator erase( const_iterator pos ){
            const difference_type temp = pos - cbegin();
            allocator_.destroy(begin_+temp);
            size_t i=0;
            for(auto m=begin()+temp+1;m<end();m++){
                allocator_.construct(begin_+temp+i,*m);
                i++;
            }
            size_--;
            end_--;
            return begin()+temp;
        }


        iterator erase( const_iterator first, const_iterator last ){
            const difference_type temp = first - cbegin();
            const difference_type temp1 = last-cbegin();
            if(temp!=0 && temp1!=0){
                size_t m=0;
                for(auto i=begin()+temp;i<begin()+temp1;i++){//first ieina, last ne
                    allocator_.destroy(begin_+temp+m);  
                    m++;
                }
                size_t k=0;
                if(begin()+temp1<end()){
                    for(auto j=begin()+temp1;j<end();j++){
                        allocator_.construct(begin_+temp+k,*(begin_+temp1+k));
                        k++;
                    }
                }
                size_=size_-(last-first);
                end_=A+size_;
                return begin()+temp;
            }
            else{
                clear();
                size_=0;
                end_=begin_;
                return begin();
            }
        }

        template< class... Args > 
        iterator emplace( const_iterator pos, Args&&... args ){//neveik
            if (size_==capacity_){
                createNewArray(std::max(1,static_cast<int>(capacity_)));//capacity_ size_t neina lygint su int...
            }
            difference_type temp = pos - cbegin();
            for(auto i=end_;i>begin_+temp;i--){
                allocator_.construct(i,*(i-1));
            }
            // allocator_.destroy(begin_+temp);
            // allocator_.construct(begin_+temp,std::forward<Args>(args)...);
            size_++;
            end_=A+size_;
            return begin() + temp;
        }

        template< class... Args >
        void emplace_back( Args&&... args ){
            if(size_==capacity_){
                createNewArray(std::max(1,static_cast<int>(capacity_)));//capacity_ size_t neina lygint su int...
            }
            allocator_.construct(end_,std::forward<Args>(args)...);
            size_++;
            end_=A+size_;
        }

        void pop_back(){
            allocator_.destroy(end_);
            size_--;
            end_--;
        }

        void resize( size_type count ){
            if(size_>=count){
                for(auto i=count;i!=size_;i++)
                allocator_.destroy(begin_+i);
            }
            else{
                createNewArray(count-size_);
            }
            size_=count;
            end_=A+size_;
        }

        void resize( size_type count, const value_type& value ){
            if(size_>=count){
                for(auto i=count;i!=size_;i++)
                allocator_.destroy(begin_+i);
            }
            else{
                createNewArray(count-size_);
                for(auto i=end_;i<end_of_range;i++){
                    allocator_.construct(i,value);
                }
            }
            size_=count;
            end_=A+size_;
        }
        


        void swap( vektor& other ){
            std::swap(other.capacity_, capacity_);
            std::swap(other.size_, size_);
            std::swap(other.A, A);
            other.begin_=other.A; 
            other.end_=other.A+other.size_;
            other.end_of_range=other.A+other.capacity_;
            begin_=A;
            end_=A+size_;
            end_of_range=A+capacity_;

        }




        


    private:
    	void createNewArray(unsigned int added){
            pointer B = allocator_.allocate(end_ - begin_ + added);// end_  - begin_ == capacity_ 

            for(size_t i = 0 ; i < capacity_; i++){ //construct until copied
                allocator_.construct( B + i, A[i] );                  
            }

            for(size_t i = 0 ; i < capacity_; i++){ 
                allocator_.destroy(A +i);             //?    reik funkcijos
            }
            allocator_.deallocate(A, capacity_);
            capacity_ = capacity_ + added;

            A = B;
            //perkelti i funkcija
            begin_ = A;
            end_ = A + size_;
            end_of_range = A + capacity_;

        }

    	size_type size_;//esamas dydis
    	size_type capacity_;//max galimas dydis dabar
        allocator_type allocator_; //Alloc allocator_
    	pointer A;

    	pointer begin_;//rodo i pirma elementa
    	pointer end_;// rodo uz paskutinio elemento
    	pointer end_of_range;//rodo uz capacity galo
};

#endif // VEKTOR_H