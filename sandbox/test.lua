print("Hello")

local s = Source()

local TaskPrint1 = Task("TaskPrint1")

function TaskPrint1:onInitialize()
    self.msg = "msg1 "..self.params.name
    return true
end

function TaskPrint1:onRun()
    print(self.params.name)
    return true
end

local TaskPrint2 = Task("TaskPrint2")

function TaskPrint2:onInitialize()
    self.msg = "msg2 "..self.params.name
    return true
end

function TaskPrint2:onRun()
    return true
end

local t0 = TaskPrint1{name="abc0"}

local t1 = TaskPrint2{name="abc1"}

s0, s1 = s:addParallel(2)

s0:addTask(t0)
s1:addTask(t1)

sr1, sr2, sr3 = s:addRace(3)

local t30 = TaskPrint1{name="abc30"}
local t31 = TaskPrint1{name="abc31"}
local t32 = TaskPrint1{name="abc32"}

sr1:addTask(t30)
sr2:addTask(t31)
sr3:addTask(t32)


function my_scope(scope)
    local t0 = TaskPrint1{name="scope0"}
        
    scope:addTask(t0)
    
    return true
end

s:addScope(my_scope)

local t4 = TaskPrint1{name="t4"}

s:addTask(t4)

function test()
    return true
end

st, sf = s:addIf(test)

st:addTask(TaskPrint1{name="TRUE"})
sf:addTask(TaskPrint1{name="FALSE"})

local d0 = TaskDelay(7000.0)

s:addTask(d0)

local d0 = TaskPrint("WIIIIIIIIIIIIIIIIIIIIIIIIIIIN")

s:addTask(d0)

function my_repeat(scope)
    scope:addTask(TaskPrint("R1"))
    scope:addTask(TaskDelay(500))
    
    return true
end
    

local su = s:addRepeat(my_repeat)
su:addTask(TaskDelay(4000))

s:addTask(TaskPrint("WOOOOOOOOOOOOOOOOOW!!!!"))

print("CHAIN")

local c = Chain(s)

print("RUN")
c:run()
