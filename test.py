import chess

board = chess.Board("rnbqkbnr/8/8/8/p7/N7/7P/1K3qNR w - - 0 1")
print(len(list(board.pseudo_legal_moves))) # 22 lets fucking go