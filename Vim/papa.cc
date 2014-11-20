#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )
#define FORit(tp,c,it) for( tp::iterator it = (c).begin(); it != (c).end(); ++it )

struct person;

typedef map<string,person*> MSP;
typedef set<string>         SS;
typedef set<person*>        SP;
MSP name_lookup;
struct person {
	string name;
	char sex;
	person *spouse;
	set<person*> parents;
	person( const string &_name ) : name(_name), sex('u'), spouse(0L), parents() {}
};
person* get_person( const string &name ) {
	MSP::iterator it = name_lookup.find( name );
	if( it != name_lookup.end() ) return it->second;
	person *p = new person(name);
	name_lookup[ name ] = p;
	return p;
}

void setsex( person *p, char s ) {
	p->sex = s;
	if( p->spouse ) p->spouse->sex = s ^ ('m'^'f');
}

void marry( person *p, person *q ) {
	p->spouse = q;
	q->spouse = p;
	if( p->sex != 'u' ) setsex(p,p->sex);
	if( q->sex != 'u' ) setsex(q,q->sex);
}

void addparent( person *p, person *c ) {
	c->parents.insert(p);
	if( p->spouse ) c->parents.insert(p->spouse);
}

void compile_parentage() {
	FORit(MSP,name_lookup,it) {
		if( it->second->parents.size() == 1)
        {
            person *par = *(it->second->parents.begin());
            if( par->spouse != 0L )
                it->second->parents.insert( par->spouse );
        }
        else if (it->second->parents.size() == 2)
        {
            person *par1 = *(it->second->parents.begin());
            person *par2 = *(it->second->parents.rbegin());
            marry(par1, par2);

            FORit(MSP,name_lookup,it2) {
                if (it2->second->parents.count(par1) || it2->second->parents.count(par2))
                {
                    addparent(par1, it2->second);
                }
            }
        }
    }
}

bool isparent( person *p, person *c ) {
	return c->parents.count(p) > 0;
}

bool isgparent( person *g, person *c ) {
	FORit(SP,c->parents,it)
		if( isparent(g,*it) )
			return true;
	return false;
}

bool isniecenephew( person *n, person *u ) {
	FORit(SP,n->parents,it) {
		if( *it == u ) continue;
		//if( *it == u || *it == u->spouse ) continue;
		FORit(SP,(*it)->parents,jt) {
			size_t c1 = u->parents.count(*jt);
			size_t c2 = 0;
			//if( u->spouse ) c2 = u->spouse->parents.count(*jt);
			if( c1+c2 > 0 )
				return true;
		}
	}
	return false;
}

int main() {
	SS Sfemale, Smale;
	SS Sparent, Schild, Smarry, Sgparent, Sgchild, Sniecenephew;
	Sfemale.insert("wife"); Sfemale.insert("daughter"); Sfemale.insert("mother");
	Sfemale.insert("niece"); Sfemale.insert("grandmother"); Sfemale.insert("granddaughter");
	Smale.insert("husband"); Smale.insert("son"); Smale.insert("father");
	Smale.insert("nephew"); Smale.insert("grandfather"); Smale.insert("grandson");
	Sparent.insert("mother"); Sparent.insert("father");
	Schild.insert("daughter"); Schild.insert("son");
	Smarry.insert("wife"); Smarry.insert("husband");
	Sgparent.insert("grandfather"); Sgparent.insert("grandmother");
	Sgchild.insert("grandson"); Sgchild.insert("granddaughter");
	Sniecenephew.insert("niece"); Sniecenephew.insert("nephew");
	bool fst = true;
	while(1) {
		string line;
		getline(cin,line);
		if( cin.eof() ) break;
		if( fst ) fst=false;
		else      cout << endl;
		name_lookup.clear();
		while( line != "" ) {
			// read relationship encoded by line
			//cerr << "See line: " << line << endl;
			stringstream ss(line);
			string n1, _, n2, rel;
			ss >> n1 >> _ >> n2 >> rel;
			n2 = n2.substr(0,n2.size()-2);
			rel = rel.substr(0,rel.size()-1);
			person *p1 = get_person(n1), *p2 = get_person(n2);
			if( Sfemale.count(rel) > 0 ) setsex(p1,'f');
			if( Smale.count(rel) > 0   ) setsex(p1,'m');
			if( Sparent.count(rel) > 0 ) addparent(p1,p2);
			if( Schild.count(rel) > 0  ) addparent(p2,p1);
			if( Smarry.count(rel) > 0  ) marry(p1,p2);
			getline(cin,line);
		}
		compile_parentage();
		FORit(MSP,name_lookup,it) {
			cerr << it->second->name << " (" << it->second->sex << "): ";
			FORit(SP,it->second->parents,jt) cerr << " " << (*jt)->name;
			cerr << endl;
		}
		getline(cin,line);
		while( line != "" && !cin.eof() ) {
			// handle query encoded by line
			stringstream ss(line);
			string _, n1, n2, rel;
			ss >> _ >> n1 >> n2 >> rel;
			n2 = n2.substr(0,n2.size()-2);
			rel = rel.substr(0,rel.size()-1);
			person *p1 = get_person(n1), *p2 = get_person(n2);
			bool has_relation=false, has_sex=false;
			if( Sfemale.count(rel) > 0 && p1->sex=='f' ) has_sex=true;
			if( Smale.count(rel)   > 0 && p1->sex=='m' ) has_sex=true;
			if( Sparent.count(rel) > 0 && isparent(p1,p2) )           has_relation=true;
			if( Schild.count(rel) > 0  && isparent(p2,p1) )           has_relation=true;
			if( Smarry.count(rel) > 0 && p1->spouse == p2 )           has_relation=true;
			if( Sgparent.count(rel) > 0 && isgparent(p1,p2) )         has_relation=true;
			if( Sgchild.count(rel) > 0 && isgparent(p2,p1)  )         has_relation=true;
			if( Sniecenephew.count(rel) > 0 && isniecenephew(p1,p2) ) has_relation=true;
			if( !has_relation )     cout << "no" << endl;
			else if( has_sex )      cout << "yes" << endl;
			else if( p1->sex=='u' ) cout << "unknown" << endl;
			else                    cout << "no" << endl;
			getline(cin,line);
		}
	}
	return 0;
}
