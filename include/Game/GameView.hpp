#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <memory>
#include <string>

#include "Color.hpp"
#include "Game/GameResult.hpp"
#include "History/MoveHistory.hpp"
#include "Player.hpp"

struct GameStatus {
  std::string currentPlayerName;
  GameResult result;
  bool isInCheck;
  int whiteScore;
  int blackScore;
};

class GameView {
 public:
  void printWelcomeMessage() const;
  void printMainMenu() const;
  void printHelp() const;
  void printRules() const;
  void printTurnPrompt(Color color) const;
  void printCapturedPieces(const Player &whitePlayer,
                           const Player &blackPlayer) const;
  void printMoveHistory(const MoveHistory &moveHistory) const;

  void printResult(GameResult result, const Player &player) const;
  void printCheckStatus(const Player &player, bool isInCheck) const;
  void printStatus(const GameStatus &status, const Player &whitePlayer,
                   const Player &blackPlayer) const;
  void printGameStartMessage() const;

  void printGoodbye() const;
  void printInvalidCommand() const;
  void printQuitConfirmation(const Player &player) const;
  void printQuitConfirmed(const Player &player) const;
  void printQuitCancelled() const;
  void printYesNoPrompt() const;

  void printResignation(const Player &player) const;

  void printDrawOffer(const Player &currentPlayer,
                      const Player &opponentPlayer) const;
  void printDrawDeclined() const;

  void printLegalMovePrompt() const;
  void printNoPieceOnSquare() const;
  void printChooseOwnPiece() const;
  void printNoLegalMoves() const;

  void printCheckmate() const;
  void printStalemate() const;

  void printPromotionMenu() const;
  void printPromotionResult(const Player &player,
                            const std::string &pieceName) const;
  void printInvalidPromotionChoice() const;

  void printInvalidInput() const;
  void printInvalidMove() const;

 private:
  void printCapturedPieceList(const Player &player) const;
  std::string coordinateToText(const Coordinate &coordinate) const;
  void printMoveRecord(const MoveRecord &record) const;
};

#endif
