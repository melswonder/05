#pragma once

#include <iostream>

class vect2
{
    private:
        int x;
        int y;
    public:
        vect2(): x(0), y(0) {}
        vect2(const vect2& other): x(other.x), y(other.y) {}
        vect2(const int num1,const int num2): x(num1), y(num2) {}
        vect2& operator=(const vect2& other)
        {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }
        ~vect2() {}

        bool operator==(const vect2& other) const
        {
            if(this->x == other.x && this->y == other.y)
                return true;
            return false;
        }

        bool operator!=(const vect2& other) const
        {
            if(this->x == other.x && this->y == other.y)
                return false;
            return true;
        }
    
        vect2 operator+(const vect2& other) const 
        {
            return vect2(this->x + other.x, this->y + other.y);
        }

        vect2 operator-(const vect2& other) const 
        {
            return vect2(this->x - other.x, this->y - other.y);
        }
    
        vect2 operator+(const int other) const 
        {
            return vect2(this->x + other, this->y + other);
        }

        vect2 operator-(const int other) const
        {
            return vect2(this->x - other, this->y - other);
        } 
        
        vect2 operator*(const int other) const 
        {
            return vect2(this->x * other, this->y * other);
        }


        vect2& operator++()
        {
            this->x++;
            this->y++;
            return *this;
        }

        vect2 operator++(int)
        {
            vect2 tmp = *this;
            this->x++;
            this->y++;
            return tmp;
        }

        vect2& operator--()
        {
            this->x--;
            this->y--;
            return *this;
        }

        vect2 operator--(int)
        {
            vect2 tmp = *this;
            this->x--;
            this->y--;
            return tmp;
        }

        int& operator[](const int index)
        {
            if(index == 0)
                return this->x;
            return this->y;
        }

        const int& operator[](const int index) const 
        {
            if(index == 0)
                return this->x;
            return this->y; 
        }

        vect2 operator-()
        {
            return *this * -1;
        }
        
        vect2& operator+=(const vect2& other)
        {
            *this = *this + other;
            return *this;
        }

        vect2& operator-=(const vect2& other)
        {
           *this = *this - other;
            return *this;
        }

        vect2& operator*=(const int other)
        {
           *this = *this * other;
            return *this;
        }
    
};

inline std::ostream& operator<<(std::ostream& os,const vect2& other)
{
    os << "{" << other[0] << ", " << other[1] << "}";
    return os;
}

inline vect2 operator*(int num,const vect2& other)
{
    return num * other;
}