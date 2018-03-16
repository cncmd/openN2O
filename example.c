/*
 *  vm command
 */
#include <neko_vm.h>
#define __H_LOAD_MODULE_EX__ "loadmodule"
#define __H_ERROR_MSG_PARAM_ERROR__ "error:params valiable (NULL or array)"
/***
 * initVM(void)
 * @return neko_vm *
 */



/////////////////////////////////// module

value getModuleFromCollection(char * k) {
   extern moduleCollections;
   printf("getModuleFromCollection>>");
   print(moduleCollections);
   print(val_field(moduleCollections, k));
   return val_field(moduleCollections, k);
}

void initModuleCollections () {
	extern moduleCollections;
	if(moduleCollections == NULL) {
		moduleCollections = alloc_object(NULL);
	}
}

value addModuleToCollection (char * k, value m) {
	extern moduleCollections;
	alloc_field(moduleCollections ,k ,m);
	printf("add module done %s\n", k);
	return val_true;
}

/////////////////////////////////////
neko_vm * initVM (void) {
	neko_vm *vm;
	value module;
	neko_global_init(NULL);
	vm = neko_vm_alloc(NULL);
	initModuleCollections();
	return vm;
}
/**
 * selectVM
 */
void selectVM(neko_vm * vm) {
	neko_vm_select(vm);
}

/***
 *  load a vm Module
 */
value loadModule(char * str/**模块路径*/ , char * aliasName) {
	value module ;
	value loader;
	value ret;
	value exc = NULL;
	value args[2];

	loader = neko_default_loader(NULL,0);
    args[0] = alloc_string(str);
    args[1] = loader;
    ret = val_callEx(loader,
    		val_field(loader,val_id(__H_LOAD_MODULE_EX__/**load module api*/)),
			args,2,&exc);

    if( exc != NULL ) {
        buffer b = alloc_buffer(NULL);
        val_buffer(b,exc);
        printf("Uncaught exception - %s\n",val_string(buffer_to_string(b)));
        return NULL;
    }
    addModuleToCollection(aliasName, ret);
	return ret;
}
/***
 * executeModule
 */
void executeModule(value module) {
    value x = val_field(module,val_id("x"));
    value f = val_field(module,val_id("f"));
    value ret;
    if( !val_is_int(x) )
         return;
    printf("x = %d\n",val_int(x));
    if( !val_is_function(f) || val_fun_nargs(f) != 1 )
         return;
    ret = val_call1(f,x);
    if( !val_is_int(ret) )
         return;
    printf("f(x) = %d\n",val_int(ret));
}


/***
 * getObject
 * 获取一个可以回收的table
 * @return value
 */


void print( value v ) {
	if( val_is_null(v) )
		printf("null");
	else if( val_is_int(v) )
		printf("int : %d",val_int(v));
	else if( val_is_float(v) )
		printf("float : %f",val_float(v));
	else if( val_is_bool(v) )
		printf("bool : %s",val_bool(v)?"true":"false");
	else if( val_is_array(v) )
		printf("array : size %d",val_array_size(v));
	else if( val_is_function(v) )
		printf("function : %d args",val_fun_nargs(v));
	else if( val_is_string(v) )
		printf("string : %s (%d bytes)",val_string(v),val_strlen(v));
	else if( val_is_object(v) )
		printf("object");
	else if( val_is_abstract(v) )
		printf("abstract of kind %X",val_kind(v));
	else
		printf("any ptr");
	printf("\n");
}

value getObject() {
  return alloc_object(NULL);
}

value getArray(size) {
  return alloc_array(size);
}

value  getObjectString(value obj, char * k) {
	value str = val_field(obj, k);
	printf("getObjectString run\n");
	print(val_field(obj, k));
	return val_string(str);
}
//setter
void setObjectProb(value obj, char * k, value v) {
	printf("setObjectProb run\n");
	alloc_field(obj, k ,v);
}

void setObjectBoolean(value obj, char * k, int  v) {
	printf("setObjectBoolean run\n");
	value pack = alloc_bool(v);
	alloc_field(obj, k ,pack);
}

void setObjectNumber(value obj, char * k, double  v) {
	printf("setObjectNumber run\n");
	value pack = alloc_float(v);
	alloc_field(obj, k ,pack);
}

void setObjectInt(value obj, char * k, int v) {
	printf("setObjectProbInt run\n");
	value pack = alloc_int(v);
	alloc_field(obj,k,pack);
}

void setObjectString (value obj, char * k , char * v) {
	value pack = alloc_string(v);
	printf("setObjectProbString [k]=%s \n [v]=%s run\n", k ,v);
	alloc_field(obj,k,pack);
}

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


value callModuleMethod (value * params) {

//	value nfuncName  = alloc_string("funcName");
//	value nmoduName  = alloc_string("moduName");
//	value nfuncParam = alloc_string("funcParam");
//
//	value funcName  = val_field(params,val_id(nfuncName));
//	value moduName  = val_field(params,val_id(nmoduName));
//	value funcParam = val_field(params,val_id(nfuncParam));
//
//	print(nfuncName);
//	print(nmoduName);
//	print(nfuncParam);


	value funcName =getObjectString(params,val_id("funcName"));
	value moduName =getObjectString(params,val_id("moduleName"));
	value funcParam=getObjectString(params,val_id("funcParam"));
//
	int cn = 0;
	int fn = 0;

	value module = getModuleFromCollection(moduName);
//
//
	if(moduName == NULL) {
		module = val_this(); /// get global namespace method
	}
//
	printf("module is ");
	print(module);
	value a = val_field(params,"funcName");
	value b = val_field(params,"moduleName");

	print(a);
	print(b);
	printf("========>\n");
//


	if(!val_is_null(funcParam)) {
		if(val_is_array(funcParam)) {
			cn = val_array_size(funcParam);
			if(val_is_function(val_field(module,funcName))) {
				fn = val_fun_nargs(val_field(module,funcName));
			} else {
				fn = 0;
			}
		}
	} else {
		funcParam = getArray(0);
	}

	printf("fn cn is ");
	printf("%d,%d", fn,cn);
	printf("========>\n");

	printf("funcName is ");
	print(funcName);
	printf("========>\n");

	printf("moduName is ");
	print(moduName);
	printf("========>\n");


//	print(val_field(module,funcName));
//	value exc = NULL;
//	value ret = val_callEx(module,
//			val_field(module,funcName),
//			funcParam,
//			cn,
//			&exc);
	printf("run tag\n");
//
//	if( exc != NULL ) {
//		buffer b = alloc_buffer(NULL);
//		val_buffer(b,exc);
//		printf("Uncaught exception - %s\n",val_string(buffer_to_string(b)));
//		return NULL;
//	}
//	return ret;
	return NULL;
}

////测试使用lua_api
void testGetVoidPoint(int a[10]) {
	printf("testGetVoidPoint==========>\n");
}

void test () {
	printf("testMulityParams==========>\n");
	value a ;
	testCaseForTypeValue();
}

void testCaseForTypeValue(value a) {
	printf("testCaseForTypeValue ok \n");
}
