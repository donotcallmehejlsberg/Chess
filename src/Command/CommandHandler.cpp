#include "Command/CommandHandler.hpp"

#include <map>
#include <optional>
#include <vector>

CommandHandler::CommandHandler(Board &board, Player &whitePlayer,
                               Player &blackPlayer, Color &currentPlayerColor,
                               GameResult &result, GameView &view,
                               BoardRenderer &renderer,
                               MoveValidator &moveValidator,
                               MoveParser &moveParser, InputReader &inputReader,
                               InputNormalizer &inputNormalizer,
                               MoveHistory &moveHistory)
    : board_(board),
      white_player_(whitePlayer),
      black_player_(blackPlayer),
      current_player_color_(currentPlayerColor),
      result_(result),
      view_(view),
      renderer_(renderer),
      move_validator_(moveValidator),
      move_parser_(moveParser),
      input_reader_(inputReader),
      input_normalizer_(inputNormalizer),
      move_history_(moveHistory) {}

CommandResult CommandHandler::handleCommand(const std::string &input) {
  static const std::map<std::string, HandlerMethod> commands = {
      {"quit", &CommandHandler::handleQuit},
      {"resign", &CommandHandler::handleResign},
      {"help", &CommandHandler::handleHelp},
      {"rules", &CommandHandler::handleRules},
      {"check", &CommandHandler::handleCheck},
      {"board", &CommandHandler::handleBoard},
      {"captured", &CommandHandler::handleCaptured},
      {"draw", &CommandHandler::handleDrawOffer},
      {"moves", &CommandHandler::handleLegalMoves},
      {"status", &CommandHandler::handleStatus},
      {"history", &CommandHandler::handleHistory}};

  const auto command = commands.find(input);
  if (command == commands.end()) {
    return CommandResult::NotCommand;
  }

  return (this->*(command->second))();
}

CommandResult CommandHandler::handleQuit() {
  view_.printQuitConfirmation(getCurrentPlayer());

  while (true) {
    const std::string answer =
        input_normalizer_.normalize(input_reader_.readLine());

    if (answer == "yes") {
      view_.printQuitConfirmed(getCurrentPlayer());
      setOpponentAsWinner();
      return CommandResult::GameEnded;
    }

    if (answer == "no") {
      view_.printQuitCancelled();
      return CommandResult::Handled;
    }

    view_.printYesNoPrompt();
  }
}

CommandResult CommandHandler::handleResign() {
  view_.printResignation(getCurrentPlayer());
  setOpponentAsWinner();
  return CommandResult::GameEnded;
}

CommandResult CommandHandler::handleDrawOffer() {
  view_.printDrawOffer(getCurrentPlayer(), getOpponentPlayer());

  const std::string answer =
      input_normalizer_.normalize(input_reader_.readLine());

  if (answer == "yes") {
    result_ = GameResult::Draw;
    return CommandResult::GameEnded;
  }

  if (answer == "no") {
    view_.printDrawDeclined();
    return CommandResult::Handled;
  }

  view_.printInvalidInput();
  return CommandResult::Handled;
}

CommandResult CommandHandler::handleBoard() {
  renderer_.printBoard(
      board_, getCurrentPlayer(),
      move_validator_.getCheckedKingCoordinate(board_, current_player_color_));
  return CommandResult::Handled;
}

CommandResult CommandHandler::handleHelp() {
  view_.printHelp();
  return CommandResult::Handled;
}

CommandResult CommandHandler::handleRules() {
  view_.printRules();
  return CommandResult::Handled;
}

CommandResult CommandHandler::handleCheck() {
  printCheckStatus();
  return CommandResult::Handled;
}

CommandResult CommandHandler::handleCaptured() {
  view_.printCapturedPieces(white_player_, black_player_);
  return CommandResult::Handled;
}

CommandResult CommandHandler::handleLegalMoves() {
  while (true) {
    view_.printLegalMovePrompt();

    const std::string input =
        input_normalizer_.normalize(input_reader_.readLine());
    if (input == "cancel") {
      return CommandResult::Handled;
    }

    const std::optional<Coordinate> from = move_parser_.parseCoordinate(input);
    if (!from.has_value()) {
      view_.printInvalidInput();
      continue;
    }

    const Piece *piece = board_.getPiece(from.value());
    if (piece == nullptr) {
      view_.printNoPieceOnSquare();
      continue;
    }

    if (piece->getPieceColor() != current_player_color_) {
      view_.printChooseOwnPiece();
      continue;
    }

    const std::vector<Coordinate> legalMoves =
        move_validator_.getLegalMovesForPiece(board_, from.value(),
                                              current_player_color_);

    if (legalMoves.empty()) {
      view_.printNoLegalMoves();
      return CommandResult::Handled;
    }

    renderer_.printBoard(
        board_, getCurrentPlayer(),
        move_validator_.getCheckedKingCoordinate(board_, current_player_color_),
        legalMoves);

    return CommandResult::Handled;
  }
}

CommandResult CommandHandler::handleStatus() {
  printStatus();
  return CommandResult::Handled;
}

CommandResult CommandHandler::handleHistory() {
  view_.printMoveHistory(move_history_);
  return CommandResult::Handled;
}

const Player &CommandHandler::getCurrentPlayer() const {
  return current_player_color_ == Color::White ? white_player_ : black_player_;
}

const Player &CommandHandler::getOpponentPlayer() const {
  return current_player_color_ == Color::White ? black_player_ : white_player_;
}

void CommandHandler::setOpponentAsWinner() {
  result_ = current_player_color_ == Color::White ? GameResult::BlackWon
                                                  : GameResult::WhiteWon;
}

void CommandHandler::printCheckStatus() const {
  const bool isInCheck =
      move_validator_.getCheckedKingCoordinate(board_, current_player_color_)
          .has_value();

  view_.printCheckStatus(getCurrentPlayer(), isInCheck);
}

void CommandHandler::printStatus() const {
  const GameStatus status{
      getCurrentPlayer().getColorName(), result_,
      move_validator_.getCheckedKingCoordinate(board_, current_player_color_)
          .has_value(),
      white_player_.getScore(), black_player_.getScore()};

  view_.printStatus(status, white_player_, black_player_);
}
