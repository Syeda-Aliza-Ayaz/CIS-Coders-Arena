import pyfiglet
import sys

candidates = ['Alice', 'Bob', 'Charlie']  # List of candidate names
candidate_data = [
    {'name': 'Alice', 'votes': 0, 'eliminated': False},
    {'name': 'Bob', 'votes': 0, 'eliminated': False},
    {'name': 'Charlie', 'votes': 0, 'eliminated': False}
]
preferences = []  # Preferences of voters
def main():    
    voters = int(input("Enter number of voters: "))
    global preferences
    preferences = [[None] * len(candidates) for _ in range(voters)]
    if voters < 1:
        print("Number of voters must be at least 1.")
        sys.exit(1)

    print(pyfiglet.figlet_format("Runoff Voting"))
    print("Welcome to the Runoff Voting System!")
    for i in range(voters):
        print(f"\nVoter {i + 1}:")
        for rank in range(len(candidates)):
            name = input(f"Rank {rank + 1} preference: ").strip()
            if not vote(i, rank, name):
                sys.exit("Invalid vote.")
    while True:
        tabulate()
        if print_winner():
            break
        min_votes = find_min()
        if is_tie(min_votes):
            print("It's a tie between:")
            for candidate in candidate_data:
                if not candidate["eliminated"]:
                    print(candidate["name"])
            break
        eliminate(min_votes)

        # Reset votes for the next round
        for candidate in candidate_data:
            candidate["votes"] = 0

def vote(voter, rank, name):
    if name in candidates:
        index = candidates.index(name)
        if preferences[voter][rank] is not None:
            print(f"Voter {voter + 1} has already ranked candidate {candidates[preferences[voter][rank]]} at rank {rank + 1}.")
            return False
        preferences[voter][rank] = index
        return True
    else:
        print(f"Candidate {name} not found.")
        return False

def tabulate():
    for voter in preferences:
        for rank in voter:
            candidate = candidate_data[rank] if rank is not None else None
            if not candidate["eliminated"]:
                candidate_data[rank]['votes'] += 1
                break

def print_winner():
    majority = len(preferences) // 2 + 1
    for candidate in candidate_data:
        if candidate["votes"] >= majority and not candidate["eliminated"]:
            print(f"Winner: {candidate['name']}")
            return True
    return False

def find_min():
    min_votes = float("inf")
    for candidate in candidate_data:
        if not candidate["eliminated"] and candidate["votes"] < min_votes:
            min_votes = candidate["votes"]
    return min_votes

def is_tie(min_votes):
    for candidate in candidate_data:
        if not candidate["eliminated"] and candidate["votes"] != min_votes:
            return False
    return True

def eliminate(min_votes):
    for candidate in candidate_data:
        if candidate["votes"] == min_votes and not candidate["eliminated"]:
            candidate["eliminated"] = True
            print(f"Candidate {candidate['name']} has been eliminated.")

if __name__ == "__main__":
    main()
    print("Voting process completed.")