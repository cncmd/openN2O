package.cpath = './?.so;'

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
example.setObjectKeyString(paramA,"funcName","f");
local arr = example.getArray(0);
example.setObjectProb(paramA,"funcParam", arr);
example.setObjectKeyString(paramA,"moduleName","test");
--example.setObjectInt(paramA,"I",1000);
print("-------------------------");
print(example.getObjectKeyString(paramA,"moduleName"));
print(example.getObjectKeyString(paramA,"funcName"));
print(example.getObjectKeyString(paramA,"funcParam"));
print("-------------------------");
print(example.callModuleMethod(paramA));
print("call func done");
print(example.getObjectKeyString(paramA,"moduleName"));

