from automata import FiniteAutomata

def printMenuFiniteAutomata():
    print("1. Set of states")
    print("2. Alphabet")
    print("3. Transitions")
    print("4. Final States")
    print("5. Verify sequence")
    print("0. Exit")

def main():

    fa = FiniteAutomata.readFromFile('fa.txt')
    cmd = -1
    while cmd != 0:
        printMenuFiniteAutomata()
        cmd = int(input())
        if cmd == 1:
            print("The set of states Q is: ", fa.Q)
        elif cmd == 2:
            print("Alphabet: ", fa.E)
        elif cmd == 3:
            print("Transitions: ", fa.D)
        elif cmd == 4:
            print("The set of final states is: ", fa.F)
        elif cmd == 5:
            sequence = input("sequence input: ")
            if fa.isAccepted(sequence):
                print("Sequence is accepted")
            else:
                print("Sequence is not accepted")
        elif cmd == 0:
            break 

main()
