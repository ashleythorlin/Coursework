#! usr/bin/env python3

import random

def display_header():
    print("BLACKJACK!")
    print("Blackjack payout is 3:2")
    print("Enter 'x' to exit")
    print()

def starting_amount():
    #starting amount
    balance = 0
    while True:
        balance = float(input("Starting amount:    "))
        if 0 < money <= 10000:
            return balance
        else:
            print("Invalid amount. Must be from 0 to 10000")

def bet_amount(amount):
    while True:
        #bet amount
        betAmt = input("Bet amount: ")
    
        #check for exit
        if betAmt.lower() == 'x':
            return betAmt
        
        #convert to float
        betAmt = float(betAmt)
        if betAmt < 5:
            print("The minimum bet is 5.")
        elif bet > 1000:
            print("The maximum bet is 1000")
        elif bet > money:
            print("You don't have enough money to make that bet.")
        else:
            return betAmt
    
def gen_outcome(balance):
    #outcomes
    outcome = random.randint(0,99)

    if outcome < 5:
        balance += (betAmt * 1.5)
        return "blackjack"

    elif outcome < 42:
        balance += betAmt
        return "win"

    elif outcome < 51:
        return "push"

    else:
        balance -= betAmt
        return "lose"
        
    print()
    

def main():
    display_header()

    start_amt = starting_amount()
    print()

    balance = start_amt
    
    #main loop
    while True:
        bet = bet_amount(amount)
        if bet == "x":
            break

        bet = get_bet()

        outcome = gen_outcome()

        if outcome.lower() == "blackjack":
            print("You got blackjack!")
            balance += round(bet * 1.5, 2)

        elif outcome.lower() == "win":
            print("You won!")
            balance += bet

        elif outcome.lower() == "push":
            print("You pushed.")

        else:
            print("You lost.")
            balance -= betAmt

        print("Money: " + str(balance))
        print()

    #program end
    print("Bye!")

if __name__ == "__main__":
    main()





