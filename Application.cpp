#include "Application.h"
#include "imgui/imgui.h"
#include "classes/TicTacToe.h"
#include "Logger.h"

namespace ClassGame {
        //
        // our global variables
        //
        TicTacToe *game = nullptr;
        bool gameOver = false;
        bool playAgainstAI = false;
        int gameWinner = -1;

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            game = new TicTacToe();
            game->setUpBoard();

            Logger::Init("engine.log");
            Logger::Info("Game started successfully");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {

                 Logger::DrawImGui();
            Logger::DrawFileConsole();
            if (ImGui::Button("Trace")){
                Logger::Trace("This is a trace message.");
            }
            if (ImGui::Button("Debug")){
                Logger::Debug("This is a debug message.");
            }
            if (ImGui::Button("Info")){
                Logger::Info("This is an info message.");
            }
            if (ImGui::Button("Warning")){
                Logger::Warning("This is a warning message.");
            }
            if (ImGui::Button("Error")){
                Logger::Error("This is an error message.");
            }
            if (ImGui::Button("Clear Log")){
                Logger::Clear();
            }
            ImGui::SameLine();

            if (ImGui::Button("Copy All")){
                Logger::CopyAllToClipboard();
            }
            ImGui::Separator();

                ImGui::DockSpaceOverViewport();

                //ImGui::ShowDemoWindow();

                if (!game) return;
                if (!game->getCurrentPlayer()) return;
                
                ImGui::Begin("Settings");
                if (ImGui::Button(playAgainstAI ? "switch to human vs human": "Switch to human vs AI")){
                    playAgainstAI = !playAgainstAI;

                    game->_gameOptions.AIPlaying = playAgainstAI;
                    
                    game->stopGame();
                    game->setUpBoard();

                    gameOver = false;
                    gameWinner = -1;
                }
                ImGui::Text("Current Player Number: %d", game->getCurrentPlayer()->playerNumber());
                ImGui::Text("Current Board State: %s", game->stateString().c_str());

                if (gameOver) {
                    ImGui::Text("Game Over!");
                    ImGui::Text("Winner: %d", gameWinner);
                    if (ImGui::Button("Reset Game")) {
                        game->stopGame();
                        game->setUpBoard();
                        gameOver = false;
                        gameWinner = -1;
                    }
                }
                ImGui::End();

                ImGui::Begin("GameWindow");
                game->drawFrame();
                ImGui::End();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
            Logger::Shutdown();

            Player *winner = game->checkForWinner();
            if (winner)
            {
                gameOver = true;
                gameWinner = winner->playerNumber();
            }
            if (game->checkForDraw()) {
                gameOver = true;
                gameWinner = -1;
            }
        }
}
