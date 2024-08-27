import catos


class AnotherScript(catos.Script):
    def __init__(self):
        print("Another start")

    def update(self):
        print("Another update")

    def end(self):
        print("Another End")