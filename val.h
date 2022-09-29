#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

enum ValType { VINT, VREAL, VSTRING, VBOOL, VERR };

class Value {
    ValType	T;
    bool    Btemp;
	int		Itemp;
	float   Rtemp;
    string	Stemp;
       
public:
    Value() : T(VERR), Btemp(false), Itemp(0), Rtemp(0.0), Stemp("") {}
    Value(bool vb) : T(VBOOL), Btemp(vb), Itemp(0), Rtemp(0.0), Stemp("") {}
    Value(int vi) : T(VINT), Btemp(false), Itemp(vi), Rtemp(0.0), Stemp("") {}
	Value(float vr) : T(VREAL), Btemp(false), Itemp(0), Rtemp(vr), Stemp("") {}
    Value(string vs) : T(VSTRING), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(vs) {}
    
    
    ValType GetType() const { return T; }
    bool IsErr() const { return T == VERR; }
    bool IsInt() const { return T == VINT; }
    bool IsString() const { return T == VSTRING; }
    bool IsReal() const {return T == VREAL;}
    bool IsBool() const {return T == VBOOL;}
    
    int GetInt() const { if( IsInt() ) return Itemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    string GetString() const { if( IsString() ) return Stemp; throw "RUNTIME ERROR: Value not a string"; }
    
    float GetReal() const { if( IsReal() ) return Rtemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    bool GetBool() const {if(IsBool()) return Btemp; throw "RUNTIME ERROR: Value not a boolean";}
    
    void SetType(ValType type)
    {
    	T = type;
	}
	
    void SetInt(int val)
    {
    	Itemp = val;
	}
	
	void SetReal(float val)
    {
    	Rtemp = val;
	}
	
	void SetString(string val)
    {
    	Stemp = val;
	}
	
	void SetBool(bool val)
    {
    	Btemp = val;
	}
	
	
    // add op to this
    Value operator+(const Value& op) const{
        Value val;
        if(Itemp == 0 && Rtemp == 0.0 && Stemp == "")
           return val;
         if(Itemp == 0 && Rtemp != 0.0 && op.IsInt())
        {
            return Rtemp + op.Itemp;
                
        }
        if(Itemp != 0 && Rtemp == 0.0 && op.IsReal())
        {
            return Itemp + op.Rtemp;
        }
        if(op.IsInt() && (Itemp ==0) && (Rtemp !=0))
        {
            float hi = (float)op.Itemp;
            return hi+Rtemp;
        }
         if(((Itemp != 0) || (Rtemp != 0)) && op.IsString())
            return val;
        else if(op.IsInt() && (Itemp != 0))
        {
            return Itemp + op.Itemp;
        }
        if(op.IsReal() && (Rtemp != 0.0))
        {
            
            return Rtemp+op.Rtemp;
        }
        
        if(op.IsString())
        {
            
                return Stemp + op.Stemp;
        }
           else{
       return val;
           }
    }
    
    // subtract op from this
    Value operator-(const Value& op) const
    {
         Value val;
       if(Itemp == 0 && Rtemp == 0.0 && Stemp == "")
           return val;
        if(op.IsInt()  && (Rtemp != 0))
        {
            return Itemp - op.Itemp;
        }
        if(op.IsReal() && (Rtemp != 0.0))
        {
            
            return Rtemp-op.Rtemp;
        }
        
        else
       return val;
    };
    
    // multiply this by op
    Value operator*(const Value& op) const
    {
        Value val;
        if(Itemp == 0 && Rtemp == 0.0 && Stemp == "")
           return val;
        if(Itemp == 0 && Rtemp != 0.0 && op.IsInt())
        {
            return Rtemp * op.Itemp;
                
        }
        if(Itemp != 0 && Rtemp == 0.0 && op.IsReal())
        {
            return Itemp * op.Rtemp;
        }
        if(op.IsInt()  && (Itemp != 0))
        {
            return Itemp * op.Itemp;
        }
        if(op.IsReal()  && (Rtemp != 0.0))
        {
            
            return Rtemp*op.Rtemp;
        }
        
        else{
       return val;
        }
    };
    
    // divide this by op
    Value operator/(const Value& op) const{
        Value val;
        if(Itemp == 0 && Rtemp == 0.0 && Stemp == "")
           return val;
        if(Itemp == 0 && Rtemp != 0.0 && op.IsInt())
        {
            return Rtemp / op.Itemp;
                
        }
        if(Itemp != 0 && Rtemp == 0.0 && op.IsReal())
        {
            return Itemp / op.Rtemp;
        }
        if(op.IsInt()  && (Itemp != 0))
        {
            return Itemp / op.Itemp;
        }
        if(op.IsReal()  && (Rtemp != 0.0))
        {
            
            return Rtemp/op.Rtemp;
        }
        
        else{
       return val;
        }
    };
    
    Value operator==(const Value& op) const
    {
        Value val;
        
       if(Itemp == 0 && Rtemp == 0.0 && Stemp == "")
           return val;
        if(Itemp == 0 && Rtemp != 0.0 && op.IsInt())
        {
            if(Rtemp == op.Itemp)
                return true;
            else
                return false;
        }
        if(Itemp != 0 && Rtemp == 0.0 && op.IsReal())
        {
            if(Itemp == op.Rtemp)
                return true;
            else
                return false;
        }
        if(((Itemp != 0) || (Rtemp != 0)) && op.IsString())
            return val;
        if(op.IsInt() && (Itemp != 0))
        {
            if(Itemp == op.Itemp)
                return true;
            else
                return false;
        }
        if(op.IsReal() && (Rtemp != 0.0))
        {
            if(Rtemp == op.Rtemp)
                return true;
            else
                return false;
        }
        if(op.IsString())
        {
            
              if(Stemp == op.Stemp)
                return true;
            else
                return false;
        }
       
       
        else
        return val;
    };

	Value operator>(const Value& op) const
    {
        Value val;
        
       if(Itemp == 0 && Rtemp == 0.0 && Stemp == "")
           return val;
        if(Itemp == 0 && Rtemp != 0.0 && op.IsInt())
        {
            if(Rtemp > op.Itemp)
                return true;
            else
                return false;
        }
        if(Itemp != 0 && Rtemp == 0.0 && op.IsReal())
        {
            if(Itemp > op.Rtemp)
                return true;
            else
                return false;
        }
        if(((Itemp != 0) || (Rtemp != 0)) && op.IsString())
            return val;
        if(op.IsInt() && (Itemp != 0))
        {
            if(Itemp > op.Itemp)
                return true;
            else
                return false;
        }
        if(op.IsReal() && (Rtemp != 0.0))
        {
            if(Rtemp > op.Rtemp)
                return true;
            else
                return false;
        }
        if(op.IsString())
        {
            
              if(Stemp > op.Stemp)
                return true;
            else
                return false;
        }
       
       
        else
        return val;
    };
	
	Value operator<(const Value& op) const
    {
        Value val;
        
       if(Itemp == 0 && Rtemp == 0.0 && Stemp == "")
           return val;
        if(Itemp == 0 && Rtemp != 0.0 && op.IsInt())
        {
            if(Rtemp < op.Itemp)
                return true;
            else
                return false;
        }
        if(Itemp != 0 && Rtemp == 0.0 && op.IsReal())
        {
            if(Itemp < op.Rtemp)
                return true;
            else
                return false;
        }
        if(((Itemp != 0) || (Rtemp != 0)) && op.IsString())
            return val;
        if(op.IsInt() && (Itemp != 0))
        {
            if(Itemp < op.Itemp)
                return true;
            else
                return false;
        }
        if(op.IsReal() && (Rtemp != 0.0))
        {
            if(Rtemp < op.Rtemp)
                return true;
            else
                return false;
        }
        if(op.IsString())
        {
            
              if(Stemp < op.Stemp)
                return true;
            else
                return false;
        }
       
       
        else
        return val;
    };
	
	    
    friend ostream& operator<<(ostream& out, const Value& op) {
        if( op.IsInt() ) out << op.Itemp;
        else if( op.IsString() ) out << op.Stemp;
        else if( op.IsReal()) out << fixed << showpoint << setprecision(2) << op.Rtemp;
        else if (op.IsBool()) {
        	if(op.GetBool()) cout << "true" ;
        	else
        		cout << "false" ;
		}
        else out << "ERROR";
        return out;
    }
};


#endif
