class FiniteAutomata:

    def __init__(self, Q, E, D, q0,F):
        self.Q = Q 
        self.E = E
        self.D = D
        self.q0 = q0 
        self.F = F 


    @staticmethod
    def parseLine(line):
        return [element.strip() for element in line.strip().split('=')[1].strip()[1:-1].split(',')]
    
    @staticmethod
    def readD(txt):
        result = [] 
        for rule in txt:
            [lhs, rhs] = rule.strip().split('-')
            [i, j] = lhs.strip()[1:-1].split(' ')
            result.append(((i, j), rhs.strip()))

        return result

    @staticmethod
    def readFromFile(fileName):

        with open(fileName) as file:
            Q = FiniteAutomata.parseLine(file.readline())
            E = FiniteAutomata.parseLine(file.readline())
            q0 = FiniteAutomata.parseLine(file.readline())
            F = FiniteAutomata.parseLine(file.readline())
            D = FiniteAutomata.readD(FiniteAutomata.parseLine(''.join([line for in file])))
        return FiniteAutomata(Q, E, D, q0, F) 

    @staticmethod
    def fromRegularGrammar(rg):

        Q = rg.N + ['K']
        E = rg.E 
        q0 = [rg.S[0]]
        D = []
        F = ['K']
        for rule in rg.P:
            lhs, rhs = rule 
            print(lhs, rhs)
            if lhs == q0[0] and rhs == 'e':
                F.append(lhs)
                continue 
            if len(rhs) == 2:
                D.append(((lhs, rhs[0]), rhs[1]))
            else:
                D.append(((lhs, rhs[0]), 'K'))
        return FiniteAutomata(Q, E, D, q0, F)

    

