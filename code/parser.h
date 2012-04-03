#ifndef parser_h_included
#define parser_h_included

#include "symbol_table.h"

typedef enum { typeRcon, typeIcon, typeId, typeOpr,typeType } nodeEnum;

/*type*/
typedef struct typeNodeType{ \
	enum type_ myTYPE; \
	}typeNodeType;
	
/* integer constants */
typedef struct iconNodeType{
    int value;                  /* value of constant */
    int nops;
} iconNodeType;

/* real constants */
typedef struct rconNodeType{
    double value;                  /* value of constant */
    int nops;
} rconNodeType;

/* identifiers */
typedef struct idNodeType{
    int i;                      /* subscript to sym array */
    int nops;
    struct symbol* ptr;	
} idNodeType;

/* operators */
typedef struct oprNodeType{
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    enum type_ nd_TYPE;
    struct nodeTypeTag **op;	/* operands */
} oprNodeType;

typedef struct nodeTypeTag { 
    nodeEnum type;             /* type of node */
    type_ abs_type;
    union {
        iconNodeType icon;        /* integer constants */
        rconNodeType rcon;        /* real constants */
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
        typeNodeType Type;
    };
} nodeType ;


#endif
