A command-line application designed to track player scores and match results.

The system utilizes File I/O to save data between sessions.

Functionalities:

1. Add Match                     
-Data Entry: Allows users to input match results using a specific format (e.g., Player1 Score1 / Score2 Player2).       
-Automatic Player Discovery: If a name is entered that doesn't exist in the database, the system automatically creates a new player profile.           
-Win/Loss Updates: Automatically calculates the winner based on the score and updates the respective win/loss records for both players.

2. Leaderboard                 
-Ranked Standings: Displays all players sorted primarily by total wins.                 
-Tie-Breaking Logic: If players have the same number of wins, the system sorts them by the fewest losses to determine the higher rank.

3. Player History                       
-Individual Statistics: Users can select a specific player to view their total career wins and losses.               
-Match Logs: Displays a filtered list of every match that specific player participated in, showing opponents and scores.

5. Persistent Data Management                      
-CSV Storage: Data is stored in players.csv and matches.csv, making the data portable and viewable in spreadsheet software like Excel.                   
-Auto-Load/Save: The system loads existing data upon startup and performs a final save upon exit to ensure no progress is lost.
