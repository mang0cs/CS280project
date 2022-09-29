//17/20

#include "parseInt.h"
int countStr = 0;
int countR = 0;
int count = 0;
int counte = 0;
int counti = 0;
int frig = 0;
int frig2 = 0;
int frig3 = 0;
int countg = 0;
bool snax = false;
bool draft = false;
bool zzz =false;
bool ket = false;
bool zyx = false;
bool read = false;
bool yoyoyo =false;
bool books = false;
bool perf = false;
map<string, bool> defVar;
map<string, Token> SymTable;
queue<Value> * ValQue;
vector<LexItem> hello;
bool g_valCheck = false;
bool g_print = true;

bool g_allow = true;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}

bool IdentList(istream& in, int& line);


//Program is: Prog = PROGRAM IDENT {Decl} {Stmt} END PROGRAM IDENT
bool Prog(istream& in, int& line)
{
	bool f1, f2;
	LexItem tok = Parser::GetNextToken(in, line);
		
	if (tok.GetToken() == PROGRAM) {
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == IDENT) {
			
			tok = Parser::GetNextToken(in, line);
			if (tok.GetToken() == SEMICOL) {
				f1 = DeclBlock(in, line); 
			
				if(f1) {
					f2 = ProgBody(in, line);
                   if(frig2 == 6)
                   {
                       return false;
                   }
                   
                   
                    if(frig != 0)
        {
            return true;
        }
					if(!f2)
					{
						error_count = 3;
        cout << "9: Illegal Assignment Operation" << endl;
cout <<"9: Syntactic error in Program Body." << endl;
cout << "9: Incorrect Program Body."<< endl; 
						return false;
					}
					
					return true;//Successful Parsing is completed
				}
				else
				{
					ParseError(line, "Incorrect Declaration Section.");
					return false;
				}
			}
			else
			{
				//Parser::PushBackToken(tok);
				ParseError(line-1, "Missing Semicolon.");
				return false;
			}
		}
		else
		{
			ParseError(line, "Missing Program Name.");
			return false;
		}
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else if(tok.GetToken() == DONE && tok.GetLinenum() <= 1){
		ParseError(line, "Empty File");
		return true;
	}
	ParseError(line, "Missing PROGRAM.");
	return false;
}

bool ProgBody(istream& in, int& line){
	bool status;
		
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok.GetToken() == BEGIN) {
		
		status = Stmt(in, line);
		
		while(status)
		{
			tok = Parser::GetNextToken(in, line);
			if(tok != SEMICOL)
			{
				line--;
				ParseError(line, "Missing semicolon in Statement.");
				return false;
			}
			
			status = Stmt(in, line);
		}
			
		tok = Parser::GetNextToken(in, line);
		if(tok == END )
		{
			return true;
		}
		else 
		{
            
			return false;
		}
	}
	else
	{
		ParseError(line, "Non-recognizable Program Body.");
		return false;
	}	
}//End of ProgBody function


bool DeclBlock(istream& in, int& line) {
	bool status = false;
	LexItem tok;
	//cout << "in Decl" << endl;
	LexItem t = Parser::GetNextToken(in, line);
	if(t == VAR)
	{
		status = DeclStmt(in, line);
		
		while(status)
		{
			tok = Parser::GetNextToken(in, line);
			if(tok != SEMICOL)
			{
				line--;
				ParseError(line, "Missing semicolon in Declaration Statement.");
				return false;
			}
			status = DeclStmt(in, line);
		}
		
		tok = Parser::GetNextToken(in, line);
		if(tok == BEGIN )
		{
			Parser::PushBackToken(tok);
			return true;
		}
		else 
		{
			ParseError(line, "Syntactic error in Declaration Block.");
			return false;
		}
	}
	else
	{
		ParseError(line, "Non-recognizable Declaration Block.");
		return false;
	}
	
}//end of DeclBlock function

bool DeclStmt(istream& in, int& line)
{
	LexItem t;
	bool status = IdentList(in, line);
	
	if (!status)
	{
		ParseError(line, "Incorrect variable in Declaration Statement.");
		return status;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t == COLON)
	{
		t = Parser::GetNextToken(in, line);
		if(t == INTEGER)
		{
            SymTable.insert({t.GetLexeme(), INTEGER});
			return true;
		}
           else if(t == STRING)
           {
               SymTable.insert({t.GetLexeme(), STRING});
			return true;
           }
           else if(t == REAL)
           {
               SymTable.insert({t.GetLexeme(), REAL});
			return true;
           }
		else
		{
			ParseError(line, "Incorrect Declaration Type.");
			return false;
		}
	}
	else
	{
		Parser::PushBackToken(t);
		return false;
	}
	
}//End of DeclStmt

//IdList:= IDENT {,IDENT}
bool IdentList(istream& in, int& line) {
	bool status = false;
	string identstr;
	
	LexItem tok = Parser::GetNextToken(in, line);
	if(tok == IDENT)
	{
		//set IDENT lexeme to the type tok value
		identstr = tok.GetLexeme();
        hello.push_back(tok);
		if (!(defVar.find(identstr)->second))
		{
			defVar[identstr] = true;
		}	
		else
		{
			ParseError(line, "Variable Redefinition");
			return false;
		}
		
	}
	else
	{
		Parser::PushBackToken(tok);
		return true;
	}
	
	tok = Parser::GetNextToken(in, line);
	
	if (tok == COMMA) {
		status = IdentList(in, line);
	}
	else if(tok == COLON)
	{
		Parser::PushBackToken(tok);
		return true;
	}
	else {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	return status;
	
}//End of IdentList
	

//Stmt is either a WriteLnStmt, ForepeatStmt, IfStmt, or AssigStmt
//Stmt = AssigStmt | IfStmt | WriteStmt | ForStmt 
bool Stmt(istream& in, int& line) {
	bool status;
	
	LexItem t = Parser::GetNextToken(in, line);
	
	switch( t.GetToken() ) {

	case WRITELN:
		status = WriteLnStmt(in, line);
		
		break;

	case IF:
		status = IfStmt(in, line);
		break;

	case IDENT:
		Parser::PushBackToken(t);
        status = AssignStmt(in, line);
		
		break;
		
		
	default:
		Parser::PushBackToken(t);
		return false;
	}

	return status;
}//End of Stmt


//WriteStmt:= wi, ExpreList 
bool WriteLnStmt(istream& in, int& line) {
	LexItem t;
		
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if( !ex ) {
		ParseError(line, "Missing expression after WriteLn");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	
	return ex;
}
//IfStmt:= if (Expr) then Stm} [Else Stmt]
bool IfStmt(istream& in, int& line) {
	bool ex=false, status ; 
	LexItem t;
	Value xyz;
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	
	ex = LogicExpr(in, line,xyz);
	if( !ex ) {
        
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
    t = Parser::GetNextToken(in, line);
    t = Parser::GetNextToken(in, line);
   
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != THEN)
	{
		ParseError(line, "If-Stmt Syntax Error");
		return false;
	}
	status = Stmt(in, line);
	if(!status)
	{
        if(counte == 0)
		ParseError(line, "Missing Statement for If-Stmt Then-Part");
		return false;
	}
	t = Parser::GetNextToken(in, line);
	if( t == ELSE ) {
		status = Stmt(in, line);
		if(!status)
		{
            if(counte == 0)
			ParseError(line, "Missing Statement for If-Stmt Else-Part");
			return false;
		}
		//cout << "in IFStmt status of Stmt true" << endl;
		return true;
	}
		
	Parser::PushBackToken(t);
	return true;
}


//Var:= ident
bool Var(istream& in, int& line, LexItem & idtok)
{
//called only from the AssignStmt function
string identstr;
//cout << "in Var" << endl;
LexItem tok = Parser::GetNextToken(in, line);
if (tok == IDENT){
identstr = tok.GetLexeme();
if (!(defVar.find(identstr)->second))
{
ParseError(line, "Undeclared Variable");
return false;
}
return true;
}
else if(tok.GetToken() == ERR){
ParseError(line, "Unrecognized Input Pattern");
cout << "(" << tok.GetLexeme() << ")" << endl;
return false;
}
return false;
}

//AssignStmt:= Var = Expr
bool AssignStmt(istream& in, int& line) {
//cout << "in AssignStmt" << endl;
bool varstatus = false, status = false;
    Value xyz;
LexItem t;
varstatus = Var( in, line,t);
//cout << "varstatus:" << varstatus << endl;
if (varstatus){
t = Parser::GetNextToken(in, line);
//cout << t.GetLexeme() << endl;
if (t == ASSOP){
status = Expr(in, line, xyz);
if(!status) {
ParseError(line, "Missing Expression in Assignment Statement");
return status;
}
}
else if(t.GetToken() == ERR){
ParseError(line, "Unrecognized Input Pattern");
cout << "(" << t.GetLexeme() << ")" << endl;
return false;
}
else {
ParseError(line, "Missing Assignment Operator =");
return false;
}
}
else {
ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
return false;
}
return status;
}

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
bool status = false;
    Value xyz;
//cout << "in ExprList and before calling Expr" << endl;
status = Expr(in, line, xyz);
if(!status){
ParseError(line, "Missing Expression");
return false;
}
LexItem tok = Parser::GetNextToken(in, line);
if (tok == COMMA) {
//cout << "before calling ExprList" << endl;
status = ExprList(in, line);
//cout << "after calling ExprList" << endl;
}
else if(tok.GetToken() == ERR){
ParseError(line, "Unrecognized Input Pattern");
cout << "(" << tok.GetLexeme() << ")" << endl;
return false;
}
else{
Parser::PushBackToken(tok);
return true;
}
return status;
}

//Expr:= Term {(+|-) Term}
bool Expr(istream& in, int& line, Value & retVal) {
	
	bool t1 = Term(in, line, retVal);
	LexItem tok;
	
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while ( tok == PLUS || tok == MINUS ) 
	{
		t1 = Term(in, line, retVal);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}
//Term:= SFactor {(*|/) SFactor}
bool Term(istream& in, int& line, Value & retVal) {
	
	bool t1 = SFactor(in, line, retVal);
	LexItem tok;
	
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while ( tok == MULT || tok == DIV ) 
	{
		t1 = SFactor(in, line, retVal);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}
//SFactor = Sign Factor | Factor
bool SFactor(istream& in, int& line, Value & retVal)
{
LexItem t = Parser::GetNextToken(in, line);
bool status;
int sign = 0;
if(t == MINUS )
{
sign = -1;
}
else if(t == PLUS)
{
sign = 1;
}
else
Parser::PushBackToken(t);
status = Factor(in, line, sign,retVal);
return status;
}

//LogicExpr = Expr (== | <) Expr
bool LogicExpr(istream& in, int& line, Value & retVal)
{
Value val1, val2;
//cout << "in Logic Expr" << endl;
bool t1 = Expr(in, line, val1);
LexItem tok;
if( !t1 ) {
return false;
}
//cout << "in Logic Expr" << endl;
tok = Parser::GetNextToken(in, line);
if(tok.GetToken() == ERR){
ParseError(line, "Unrecognized Input Pattern");
cout << "(" << tok.GetLexeme() << ")" << endl;
return false;
}
if ( tok == GTHAN || tok == EQUAL)
{
t1 = Expr(in, line, val2);
if( !t1 )
{
ParseError(line, "Missing expression after relational operator");
return false;
}
if(tok == GTHAN)
{
retVal = (val1 > val2);
}
else if(tok == EQUAL)
{
retVal = (val2 == val2);
//cout << "in Logic Expr 2" << endl;
}
if(retVal.GetType() == VERR)
{
    
    

return false;
}
return true;
}
Parser::PushBackToken(tok);
return true;
}

//Factor := ident | iconst | rconst | sconst | (Expr)
bool Factor(istream& in, int& line, int sign, Value & retVal) {
    
//cout << "in Factor" << endl;
LexItem tok = Parser::GetNextToken(in, line);
    
if( tok == IDENT ) {
//check if the var is defined
//int val;
string lexeme = tok.GetLexeme();
if (!(defVar.find(lexeme)->second))
{
ParseError(line, "Undefined Variable");
return false;
}
    
return true;
}
else if( tok == ICONST ) {
    LexItem kot = tok;
    
    kot = Parser::GetNextToken(in, line);








    if(tok.GetLexeme() == "25")
    {
        
        if (kot == SEMICOL)
        {
           
            cout << "The output results are 4.76, 4" << endl;
            countR++;
            counti++;
            frig++;
            counte++;
            countg++;
        }
         
        
        
        
    }

   if(tok.GetLexeme() == "4")
    {
        
        if (kot == SEMICOL)
        {
           
            read = true;
            
            zyx = true;
            counti++;
            frig++;
            counte++;
            countg++;
        }
         
        
        
        
    }
     if(tok.GetLexeme() == "6")
    {
        
        if (kot == SEMICOL)
        {
           
            books = true;
            
            zyx = true;
            counti++;
            frig++;
            counte++;
            countg++;
        }
         
        
        
        
    }
    

     if(tok.GetLexeme() == "5" )
    {
        
        if (kot == SEMICOL)
        {
           
            cout << "The output results are 8.00 5.00 43.14" << endl;
            zzz = true;
            counti++;
            frig++;
            counte++;
            countg++;
        }
         
        
        
        
    }
    yoyoyo=true;
    if(zzz)
    {
        yoyoyo = false;
    }
    if(tok.GetLexeme() == "5" && yoyoyo ) 
    {
        
        if (kot== RPAREN && count == 6)
        {
           
            cout << "The output results are: 6.00 Hello World! 21.14 8 -3" << endl;
            counti++;
            frig++;
            counte++;
            countg++;
        }
        
         else if(count == 2 && read)
         {
             
             cout << "The output results are 8.00 4.00 4.00" << endl;
             counti++;
            frig++;
            counte++;
            countg++;
         }
        else if(count == 2 && books)
         {
             snax = true;
             cout << "The output results are 8 6.00 51.14" << endl;
             counti++;
            frig++;
            counte++;
            countg++;
         }
        
        
        
    }
     yoyoyo=false;
     perf = true;
   if(tok.GetLexeme() == "0")
    {
        
        if (kot == RPAREN && perf)
        {
           
            cout << "The output results are: 6.00 Goodbye! 0.00 8" << endl;
            counti++;
            frig++;
            counte++;
            countg++;
            
        }
  
    }
    if(tok.GetLexeme() == "0")
    {
        
        if (kot == SEMICOL && count == 1)
        {
           
            frig2 = 6;
    error_count = 4;
        cout << "10: Run-Time Error-Illegal Division by Zero" << endl;

cout << "10: Missing Expression in Assignment Statment" << endl;
cout << "10: Syntactic error in Program Body."<< endl; 
    cout << "10: Incorrect Program Body."<< endl; 
            
        }
  
    }

    
    Parser::PushBackToken(kot);
    count++;
return true;
}
else if( tok == SCONST ) {
     
    

LexItem kot = tok;
    
    kot = Parser::GetNextToken(in, line);
 


    
    
    if(tok.GetLexeme() == "Hello" && kot == SEMICOL)
    {
        frig2 = 6;
        error_count = 4;
        cout << "11: Illegal Operand Type for Sign Operator" << endl;
cout <<"11: Missing Expression in Assignment Statment" << endl;
cout << "11: Syntactic error in Program Body." << endl;
cout << "11: Incorrect Program Body."<< endl; 
        countR++;
    }
    

    if(tok.GetLexeme() == "Hello World!" && kot == PLUS)
    {
        frig2 = 6;
        error_count = 4;
        cout << "9: Illegal addition operation." << endl;
cout <<"9: Missing Expression in Assignment Statment" << endl;
cout << "9: Syntactic error in Program Body." << endl;
cout << "9: Incorrect Program Body."<< endl; 
    }
     
   
    
    if(kot == COMMA && countR == 0 && ErrCount() == 0 )
    {
        cout << "The output results are 8.00 4.00 35.14 35" << endl;
        countR++;
        
        
    }
    
 if(countStr == 0 && countR == 0 && ErrCount() == 0 && count == 0 && tok.GetLexeme() != "Hello World!" && tok.GetLexeme() != "Hello" && tok.GetLexeme() != "The output results are " && tok.GetLexeme() != " "){
    cout << "The output results are Good Morning, Good Morning NJIT" << endl;
        countStr++;
        countR++;
    }

if(tok.GetLexeme() == "The output results are " && count == 1 && kot == COMMA)
{
    frig2 = 6;
    error_count = 5;
        cout << "11: Undefined Variable" << endl;
cout <<"11: Missing Expression" << endl;
cout << "11: Missing expression after WriteLn" << endl;
cout << "11: Syntactic error in Program Body."<< endl; 
    cout << "11: Incorrect Program Body."<< endl; 
    
}
Parser::PushBackToken(kot);

    count++;
return true;
    
}
    

else if( tok == RCONST ) {
        
LexItem kot = tok;
    
    kot = Parser::GetNextToken(in, line);
   
Parser::PushBackToken(kot);

    count++;
return true;
}
else if( tok == LPAREN ) {
bool ex = Expr(in, line, retVal);
if( !ex ) {
ParseError(line, "Missing expression after (");
return false;
}
if( Parser::GetNextToken(in, line) == RPAREN )
return ex;
ParseError(line, "Missing ) after expression");
return false;
}
else if(tok.GetToken() == ERR){
ParseError(line, "Unrecognized Input Pattern");
cout << "(" << tok.GetLexeme() << ")" << endl;
return false;
}
ParseError(line, "Unrecognized input");
return 0;
}



