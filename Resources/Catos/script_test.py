import script_test


class ScriptTest(catos.Script):
    def __init__(self):
        print("start")

    def update(self):
        print("update")

    def end(self):
        print("end")