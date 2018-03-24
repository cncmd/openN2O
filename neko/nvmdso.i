
%module example
%{
#include <neko_vm.h>
#include "example.h"
%}



neko_vm * initVM (void) ;
void selectVM(neko_vm * vm) ;
void executeModule(value module);


//=================================module==========

/***
 *  callModuleMethod
 *	调用某个模块的方法
 *	@param value params
 *  params 是对象类型包含必要的三个字段
 *  moduName  char *  要查找的模块， 如果没有这个字段的话，调用会在当前域里寻找
 *	funcName  char *  必须要有 如果没有这个名称的话，调用失败
 *	funcParam 数组   可以没有，如果没有的话调用的是无参数方法
 *	@return value 调用结果
 */
value callModuleMethod (value params) ;
/***
 *  模块的集合
 */
//extern value moduleCollections = NULL;

value getModuleFromCollection(value k);

void initModuleCollections () ;

value addModuleToCollection (char * k, value m) ;
value loadModule(char * str/**模块路径*/ , char * aliasName);




/////////==================std;
/***
 * getObject
 * 获取一个可以回收的table
 * @return value
 * 需要拆分到一个std的lib里
 */
value getObject();
value getArray(int size);
char * getObjectString(value obj, char * k);
char * getObjectKeyString(value obj, char * k);
void setObjectKeyString (value obj, char * k , char * v);
/***
 * setObjectProb
 * 获取一个可以回收的table
 * @return value
 * 需要拆分到一个std的lib里
 */
void setObjectProb(value obj, char * k, value v) ;
void setObjectInt(value obj, char * k, int v);
void setObjectString (value obj, char * k , char * v);

void setObjectBoolean(value obj, char * k, int  v);
void setObjectNumber(value obj, char * k, double  v);
void print(value v) ;


void test ();
void testGetVoidPoint(int a[10]) ;

