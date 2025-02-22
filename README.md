# Knight's Tour Solver in C 🏇  

This project implements a **Knight's Tour solver** on a **5x5 chessboard** using recursion and depth-first search (DFS). The program finds all possible knight’s paths from a given starting position and attempts to find a path that covers the entire board without revisiting any square.  

## **📌 Features**  
- Generates a **path tree** representing all possible knight moves.  
- Searches for a **complete knight’s tour** that visits every square exactly once.  
- **Displays the path** visually on the board.  
- **Handles duplicate moves** to ensure valid paths.  

## **🚀 How It Works**  
1. The user inputs a starting position (e.g., `A1` to `E5`).  
2. The program builds a **tree of all possible paths**.  
3. It searches for a **valid path covering the entire board**.  
4. If a valid path is found, it prints the board with the knight's move order.  

## **🛠️ Technologies Used**  
- **C programming language**  
- **Depth-First Search (DFS)** for path generation  
- **Recursive algorithms** for pathfinding  

