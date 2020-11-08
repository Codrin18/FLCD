class FiniteAutomata:

    def __init__(self, Q, E, D, q0,F):
        self.Q = Q 
        self.E = E
        self.D = D
        self.q0 = q0 
        self.F = F 


    @staticmethod
    def parseLine(line):
        """
        Read elemments between curly brackets and return them in lists
        Paramaters
        ----------
            line: string , current line from text file
        
        Return: a list of chars 
        """
        return [element.strip() for element in line.strip().split('=')[1].strip()[1:-1].split(',')]
    
    @staticmethod
    def readD(txt):
        """
        Read the transitions(D) of the finite automata from file
        Paramaters
        ----------
            txt: string from file between '{}'

        Return: a list of tuples 
        """

        result = [] 
        for rule in txt:
            [lhs, rhs] = rule.strip().split('-')
            [i, j] = lhs.strip()[1:-1].split(' ')
            result.append(((i, j), rhs.strip()))

        return result

    @staticmethod
    def readFromFile(fileName):
        """
        Read a finite automata from a file and store it in an object
        Q - list of characters
        E - list of characters
        D - list of tuples (('p', '0'), 'q')
        q0 - list of characters
        F - list of characters
        ----------
        Paramaters
            fileName : text file from which we read
        ----------
        Return : a finite automata object
        """

        with open(fileName) as file:
            Q = FiniteAutomata.parseLine(file.readline())
            E = FiniteAutomata.parseLine(file.readline())
            q0 = FiniteAutomata.parseLine(file.readline())
            F = FiniteAutomata.parseLine(file.readline())
            D = FiniteAutomata.readD(FiniteAutomata.parseLine(''.join([line for line in file])))
        return FiniteAutomata(Q, E, D, q0, F)     
    
    def checkAlphabet(self, sequence):
        """
        Check if a sequence contains only characters from the finite automata alphabet
        ----------
        Paramaters
            sequence : string 
        ----------
        Return : True if the sequence contains only charactefrs from the finite automata alphabet
                 False otherwise
        """
        ok = [ch for ch in sequence if ch in self.E]
        if len(ok) < len(sequence):
            return False 
        return True 

    def isAccepted(self, sequence):
        """
        Check if a sequence is accepted by the finite automata
        ----------
        Paramaters
            sequence : string 
        ----------
        Return : True if sequence is accepted
                 False otherwise
        """
        if not self.checkAlphabet(sequence):
            print("Alphabet of the sequence is wrong")
            return False 

        #Iterate transitions and check if we reach epsilon(empty word)
        currentState = self.q0[0]
        print(self.D)
        for currentChar in sequence:
            foundTransition = False 
            #Check if we can transit 
            for transition in self.D:
                if foundTransition:
                    continue
                if currentState == transition[0][0] and currentChar == transition[0][1]:
                    #Successfully found a transition from this state 
                    currentState = transition[1]
                    foundTransition = True 
            #If we did not find a transition
            if not foundTransition:
                return False

        if currentState in self.F:
            return True
            
        return False 
            

