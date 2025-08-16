use std::usize;

#[derive(Copy, Clone, PartialEq, Eq, Debug)]
pub enum PositionStatus {
    Free,
    Queen,
    Blocked,
}

pub fn add_queen_and_threats(board: &mut Vec<Vec<PositionStatus>>, queen_position: (usize, usize)) {
    assert_eq!(
        board[queen_position.0][queen_position.1],
        PositionStatus::Free
    );
    let n = board.len();

    let threat_points = (0..n)
        .flat_map(|idx: usize| {
            [
                (queen_position.0, idx),
                (idx, queen_position.1),
                (queen_position.0 + idx, queen_position.1 + idx),
                (queen_position.0 + idx, queen_position.1.wrapping_sub(idx)),
                (queen_position.0.wrapping_sub(idx), queen_position.1 + idx),
                (
                    queen_position.0.wrapping_sub(idx),
                    queen_position.1.wrapping_sub(idx),
                ),
            ]
        })
        .filter(|pos| pos.0 < n && pos.1 < n && pos != &queen_position);

    for threat_point in threat_points {
        board[threat_point.0][threat_point.1] = PositionStatus::Blocked;
    }

    board[queen_position.0][queen_position.1] = PositionStatus::Queen;
}

/// currentPosition holds the first idx we can change
pub fn recursive_board_build(
    num_of_queens: usize,
    current_board: Vec<Vec<PositionStatus>>,
    current_position: (usize, usize),
) -> Vec<Vec<Vec<PositionStatus>>> {
    let n = current_board.len();

    if num_of_queens == n {
        return vec![current_board];
    }

    if current_position.0 >= n || current_position.1 >= n {
        return Vec::new();
    }

    let mut next_position = (current_position.0, current_position.1);
    if current_position.1 == n - 1 {
        next_position.0 = current_position.0 + 1;
        next_position.1 = 0;
    } else {
        next_position.1 += 1;
    }

    if current_board[current_position.0][current_position.1] == PositionStatus::Blocked {
        return recursive_board_build(num_of_queens, current_board, next_position);
    }

    assert_eq!(
        current_board[current_position.0][current_position.1],
        PositionStatus::Free
    );

    let mut new_board_1 = current_board.clone();
    add_queen_and_threats(&mut new_board_1, current_position);
    let new_board_2 = current_board.clone();
    let mut possible_boards_1 =
        recursive_board_build(num_of_queens + 1, new_board_1, (current_position.0 + 1, 0));
    let possible_boards_2 = recursive_board_build(num_of_queens, new_board_2, next_position);
    possible_boards_1.extend(possible_boards_2.into_iter());

    possible_boards_1
}

pub fn board_to_board_str(board: Vec<Vec<PositionStatus>>) -> Vec<String> {
    let mut board_str = vec![String::new(); board.len()];
    for (line_idx, board_line) in board.iter().enumerate() {
        for status in board_line {
            let ch = match status {
                PositionStatus::Free => {
                    panic!("Not possible in an n x n board to have n queens with a free square")
                }
                PositionStatus::Queen => 'Q',
                PositionStatus::Blocked => '.',
            };
            board_str[line_idx].push(ch);
        }
    }

    board_str
}

pub fn solve_n_queens(n: i32) -> Vec<Vec<String>> {
    let empty_line = vec![PositionStatus::Free; n.try_into().unwrap()];
    let empty_board = vec![empty_line; n.try_into().unwrap()];
    let boards = recursive_board_build(0, empty_board, (0, 0));
    let mut boards_str = vec![];
    for board in boards {
        boards_str.push(board_to_board_str(board));
    }

    boards_str
}

fn main() {
    println!("Hello, world!");
    let n = 9;
    let result = solve_n_queens(n);

    println!("Total solutions for {}-Queens: {}", n, result.len());

    for board in &result {
        for row in board {
            println!("{}", row);
        }
        println!();
    }

    println!("Goodbye, world!");
}
