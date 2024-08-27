import catos


class ScriptTest(catos.Script):
    def __init__(self):
        print("Start")

    def update(self):
        print("Update")

    def end(self):
        print("End")