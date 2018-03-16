package.cpath = './?.so;'
cjson=require("struct");
print(cjson);

print(package.loadlib);

install,b,c = package.loadlib("./example.so","luaopen_example");

print(install,b,c);

install();

print("vm test")

local vm = example.initVM();
print(vm);
example.selectVM(vm);
--print("1");

local module = example.loadModule("mymodule.n", "test")
print(module);
example.executeModule(module);

print("==============");
local paramA = example.getObject(); 
--example.test();
--example.setObjectBoolean(paramA,"b",1);
--example.setObjectNumber(paramA,"d",3.14);
example.setObjectString(paramA,"funcName","f");
local arr = example.getArray(0);
example.setObjectProb(paramA,"funcParam", arr);
example.setObjectString(paramA,"moduleName","test");
--example.setObjectInt(paramA,"I",1000);
print("-------------------------");
print(example.getObjectString(paramA,"moduleName"));
print(example.getObjectString(paramA,"funcName"));
print(example.getObjectString(paramA,"funcParam"));
print("-------------------------");
example.callModuleMethod(paramA);
print("call func done");
print(example.getObjectString(paramA,"moduleName"));
