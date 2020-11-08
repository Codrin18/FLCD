import re 

class Grammar:

    def __init__(self, N, E, P, S):
        self.N = N 
        self.E = E 
        self.P = P 
        self.S = S 

    @staticmethod
    def parseLine(line):
        return [element.strip() for element in line.strip().split('=')[1].strip()[1:-1].split(',')]

    @staticmethod
    def parseProductions(productions):
        result = []
        for rule in productions:
            [lhs, rhs] = rule.strip().split('->')
            results = rhs.strip().split('|')
            for res in results:
                result.append((lhs.strip(), res.strip()))
        return result

    @staticmethod
    def readFromFile(fileName):
        with open(fileName) as file:
            N = Grammar.parseLine(file.readline())
            E = Grammar.parseLine(file.readline())
            S = Grammar.parseLine(file.readline())
            P = Grammar.parseProductions(Grammar.parseLine(''.join([line for line in file])))
        return Grammar(N, E, P, S)

    def getProductions(self, symbol):
        result = []
        for production in self.P:
            if production == symbol:
                result.append(production[1])
        return result

    def checkForstartingsymbolInRHS(self):
        for (lhs, rhs) in self.P:
            if re.findall(self.S[0], rhs):
                return False
        return True 

    def checkRegular(self):
        startingSymbol = self.S[0]
        for rule in self.P:
            lhs, rhs = rule 
            print(lhs, rhs)
            if len(rhs) > 2:
                return False 
            for elem in self.getProductions(rhs):
                if re.match(r'^[a-z]{1}[A-Z]{1}$|^[a-z]{1}$', elem) is None:
                    return False 
            if lhs == startingSymbol and rhs == 'e':
                if self.checkForstartingsymbolInRHS() is False:
                    return False 
        return True 


    @staticmethod
    def fromFiniteAutomata(fa):
        N = fa.Q
        E = fa.E 
        S = fa.q0
        P = []
        if fa.q0[0] in fa.F:
            P.append((fa.q0[0], 'e'))
        for transition in fa.D:
            lhs, state = transition[0]
            rhs = transition[1].strip[1]
            if rhs in fa.F:
                P.append((lhs, state))
                P.append((lhs, state.strip() + rhs))
            if rhs not in  fa.F:
                P.append((lhs, state.strip() + rhs))
        return Grammar(N, E, P, S)