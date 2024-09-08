import catos


class ScriptTest(catos.Script):
    def __init__(self):

        foo = catos.Foo()
        foo.data = 2

        foo.test()
        print("Start ", foo.data)

    def update(self):
        print("Update")

    def end(self):
        print("End")