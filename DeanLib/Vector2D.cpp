#include "Vector2D.h"
#include <cmath>

Vector2D gZeroVector2D( 0.0f, 0.0f );

Vector2D::Vector2D(float x, float y)
:mX(x)
,mY(y)
{
}

Vector2D::Vector2D( const Vector2D& rhs )
:mX( rhs.mX )
,mY( rhs.mY )
{
}

Vector2D::~Vector2D()
{
}

Vector2D& Vector2D::operator += ( const Vector2D& rhs )
{
	mX += rhs.mX;
	mY += rhs.mY;
	return *this;
}

Vector2D& Vector2D::operator -= ( const Vector2D& rhs )
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	return *this;
}

Vector2D& Vector2D::operator = ( const Vector2D& rhs )
{
	mX = rhs.mX;
	mY = rhs.mY;
	return *this;
}

Vector2D& Vector2D::operator *= ( float mult )
{
	mX *= mult;
	mY *= mult;
	return *this;
}

Vector2D& Vector2D::operator /= ( float div )
{
	mX /= div;
	mY /= div;
	return *this;
}

const Vector2D Vector2D::operator+(const Vector2D &other) const 
{
    Vector2D result = *this;     
    result += other;            
    return result;              
}

const Vector2D Vector2D::operator-(const Vector2D &other) const 
{
    Vector2D result = *this;     
    result -= other;            
    return result;              
}

const Vector2D Vector2D::operator*(float mult) const 
{
    Vector2D result = *this;     
	result.mX *= mult;
	result.mY *= mult;

    return result;              
}

bool Vector2D::operator==( const Vector2D& rhs )
{
	if ((getX() == rhs.getX()) && (getY() == rhs.getY()))
		return true;
	else return false;
}

bool Vector2D::operator!=( const Vector2D& rhs )
{
	if ((getX() == rhs.getX()) && (getY() == rhs.getY()))
		return false;
	else return true;
}

bool Vector2D::hasNonZeroLength() const
{
	if( mX != 0.0f || mY != 0.0f )
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Vector2D::getLength() const
{
	float lengthSquared = getLengthSquared();
	return sqrt( lengthSquared );
}

float Vector2D::getLengthSquared() const
{
	float lengthSquared = ( mX * mX ) + ( mY * mY );
	return lengthSquared;
}

void Vector2D::normalize()
{
	float invLength = 1.0f / (getLength() + FLT_MIN);
	mX *= invLength;
	mY *= invLength;
}