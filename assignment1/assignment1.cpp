#include <iostream>
#include <fstream>

using namespace std;

void pluss(int ***centers, char **grid, int row, int col, int size);
void minuss(int ***centers, char **grid, int row, int col, int size);
void crosss(int ***centers, char **grid, int row, int col, int size);
void slashh(int ***centers, char **grid, int row, int col, int size);

bool addition(int ***centers, char **grid, int row, int col, int size, int N, int M);
bool subtraction(int ***centers, char **grid, int row, int col, int size, int N, int M);
bool multiplication(int ***centers, char **grid, int row, int col, int size, int N, int M);
bool division(int ***centers, char **grid, int row, int col, int size, int N, int M);
bool extra_conflict(char **grid, char type, int row, int col, int size);

bool MV(int ***centers, char **grid, int row, int col, int move, char move_letter, int N, int M);
bool extra_conflict_move(char **grid, char type, int row, int col, int temp_row, int temp_col, int size);

int main(int argc, char **argv)
{
	ifstream read_grid;
	read_grid.open(argv[1]);
	
	int N = 1, M = 1;
	read_grid >> N >> M;
	
	char **grid;
	grid = new char *[N];
	for (int i = 0; i < N; i++) {
		grid[i] = new char[M];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			grid[i][j] = '\0';
		}
	}
	
	int ***centers;
	centers = new int **[N]();
	for (int i = 0; i < N; i++) {
		centers[i] = new int *[M]();
		for (int j = 0; j < M; j++) {
			centers[i][j] = new int [3]();
		}
	}
	
	char type = '\0';
	int row = 0, col = 0, size = 0;
	while (!read_grid.eof()) {
		read_grid >> type;
		read_grid >> row;
		read_grid >> col;
		read_grid >> size;
		row--;
		col--;
		if (read_grid.eof()) {
			break;
		}
		if (type != '+' && type != '-' && type != 'x' && type != '/') {
			break;
		}
		if (row > N - 1 || row < 0) {
			cout << "BORDER ERROR: Operator " << type << " with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
			extra_conflict(grid, type, row, col, size);
			continue;
		}
		if (col > M - 1 || col < 0) {
			cout << "BORDER ERROR: Operator " << type << " with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
			extra_conflict(grid, type, row, col, size);
			continue;
		}
		switch (type) {
			case '+':
				addition(centers, grid, row, col, size, N, M);
				break;
			case '-':
				subtraction(centers, grid, row, col, size, N, M);
				break;
			case 'x':
				multiplication(centers, grid, row, col, size, N, M);
				break;
			case '/':
				division(centers, grid, row, col, size, N, M);
				break;
			default:
				return 1;
		}
	}
	read_grid.close();
	
	ifstream read_instructions;
	read_instructions.open(argv[2]);
	
	type = '\0';
	row = 0;
	col = 0;
	int move = 0;
	int temp = 0;
	
	while(!read_instructions.eof()) {
		read_instructions.get();
		read_instructions.get();
		read_instructions.get(type);
		read_instructions >> row;
		read_instructions >> col;
		read_instructions >> move;
		row--;
		col--;
		if (read_instructions.eof()) {
			break;
		}
		if (type != 'R' && type != 'L' && type != 'U' && type != 'D') {
			break;
		}
		temp = row;
		row = centers[row][col][0];
		col = centers[temp][col][1];
		switch (type) {
			case 'R':
				MV(centers, grid, row, col, move, 'R', N, M);
				break;
			case 'L':
				MV(centers, grid, row, col, move, 'L', N, M);
				break;
			case 'U':
				MV(centers, grid, row, col, move, 'U', N, M);
				break;
			case 'D':
				MV(centers, grid, row, col, move, 'D', N, M);
				break;
			default:
				return 1;
		}
	}
	
	read_instructions.close();
	for (int i = 0; i < N; i++) {
		delete[] grid[i];
	}
	delete[] grid;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			delete[] centers[i][j];
		}
		delete[] centers[i];
	}
	delete[] centers;
	return 0;
}

void pluss(int ***centers, char **grid, int row, int col, int size) {
	for (int i = col - size + 1; i <= col + size + 1; i++) {
		grid[row][i] = '+';
		centers[row][i][0] = row;
		centers[row][i][1] = col;
		centers[row][i][2] = size;
	}
	for (int i = row - size + 1; i <= row + size + 1; i++) {
		grid[i][col] = '+';
		centers[i][col][0] = row;
		centers[i][col][1] = col;
		centers[i][col][2] = size;
	}
}

void minuss(int ***centers, char **grid, int row, int col, int size) {
	for (int i = col - size + 1; i <= col + size + 1; i++) {
		grid[row][i] = '-';
		centers[row][i][0] = row;
		centers[row][i][1] = col;
		centers[row][i][2] = size;
	}
}

void crosss(int ***centers, char **grid, int row, int col, int size) {
	for (int i = row - size + 1, j = col - size + 1; i <= row + size + 1 && j <= col + size + 1; i++, j--) {
		grid[i][j] = 'x';
		centers[i][j][0] = row;
		centers[i][j][1] = col;
		centers[i][j][2] = size;
	}
	for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
		grid[i][j] = 'x';
		centers[i][j][0] = row;
		centers[i][j][1] = col;
		centers[i][j][2] = size;
	}
}

void slashh(int ***centers, char **grid, int row, int col, int size) {
	for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
		grid[i][j] = '/';
		centers[i][j][0] = row;
		centers[i][j][1] = col;
		centers[i][j][2] = size;
	}
}

bool addition(int ***centers, char **grid, int row, int col, int size, int N, int M) {
	if (col > M - size - 1 || col < size || row > N - size - 1 || row < size) {
		cout << "BORDER ERROR: Operator + with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
		extra_conflict(grid, '+', row, col, size);
		return false;
	} else {
		for (int i = col - size + 1; i <= col + size + 1; i++) {
			if (grid[row][i] != '\0') {
				cout << "CONFLICT ERROR: Operator + with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
				return false;
			}
		}
		for (int i = row - size + 1; i <= row + size + 1; i++) {
			if (grid[i][col] != '\0') {
				cout << "CONFLICT ERROR: Operator + with size " << size << " can not be placed on (" << row << "," << col << ")." << endl;
				return false;
			}
		}
		
		pluss(centers, grid, row, col, size);
	}
	cout << "SUCCESS: Operator + with size " << size << " is placed on (" << row + 1 << "," << col + 1 << ")." << endl;
	return true;
}

bool subtraction(int ***centers, char **grid, int row, int col, int size, int N, int M) {
	if (col > M - size || col < size) {
		cout << "BORDER ERROR: Operator - with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
		extra_conflict(grid, '-', row, col, size);
		return false;
	} else {
		for (int i = col - size + 1; i <= col + size + 1; i++) {
			if (grid[row][i] != '\0') {
				cout << "CONFLICT ERROR: Operator - with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
				return false;
			}
		}
		
		minuss(centers, grid, row, col, size);
	}
	cout << "SUCCESS: Operator - with size " << size << " is placed on (" << row + 1 << "," << col + 1 << ")." << endl;
	return true;
}

bool multiplication(int ***centers, char **grid, int row, int col, int size, int N, int M) {
	if (col > M - size || col < size || row > N - size || row < size) {
		cout << "BORDER ERROR: Operator x with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
		extra_conflict(grid, 'x', row, col, size);
		return false;
	} else {
		for (int i = row - size + 1, j = col - size + 1; i <= row + size + 1 && j <= col + size + 1; i++, j--) {
			if (grid[i][j] != '\0') {
				cout << "CONFLICT ERROR: Operator x with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
				return false;
			}
		}
		
		for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
			if (grid[i][j] != '\0') {
				cout << "CONFLICT ERROR: Operator x with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
				return false;
			}
		}
		
		crosss(centers, grid, row, col, size);
	}
	cout << "SUCCESS: Operator x with size " << size << " is placed on (" << row + 1 << "," << col + 1 << ")." << endl;
	return true;
}

bool division(int ***centers, char **grid, int row, int col, int size, int N, int M) {
	if (col > M - size || col < size || row > N - size || row < size) {
		cout << "BORDER ERROR: Operator / with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
		extra_conflict(grid, '/', row, col, size);
		return false;
	} else {
		for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
			if (grid[i][j] != '\0') {
				cout << "CONFLICT ERROR: Operator / with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
				return false;
			}
		}
		
		slashh(centers, grid, row, col, size);
	}
	cout << "SUCCESS: Operator / with size " << size << " is placed on (" << row + 1 << "," << col + 1 << ")." << endl;
	return true;
}

bool extra_conflict(char **grid, char type, int row, int col, int size) {
	switch (type) {
		case '+':
			for (int i = col - size + 1; i <= col + size + 1; i++) {
				if (grid[row][i] != '\0') {
					cout << "CONFLICT ERROR: Operator + with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			for (int i = row - size + 1; i <= row + size + 1; i++) {
				if (grid[i][col] != '\0') {
					cout << "CONFLICT ERROR: Operator + with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		case '-':
			for (int i = col - size + 1; i <= col + size + 1; i++) {
				if (grid[row][i] != '\0') {
					cout << "CONFLICT ERROR: Operator - with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		case 'x':
			for (int i = row - size + 1, j = col - size + 1; i <= row + size + 1 && j <= col + size + 1; i++, j++) {
				if (grid[i][j] != '\0') {
					cout << "CONFLICT ERROR: Operator x with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i++, j++) {
				if (grid[i][j] != '\0') {
					cout << "CONFLICT ERROR: Operator x with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		case '/':
			for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
				if (grid[i][j] != '\0') {
					cout << "CONFLICT ERROR: Operator / with size " << size << " can not be placed on (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		default:
			break;
	}
	return true;
}

bool MV(int ***centers, char **grid, int row, int col, int move, char move_letter, int N, int M) {
	int temp_row = 0, temp_col = 0;
	int size = centers[row][col][2];
	char type = grid[row][col];
	switch (type) {
		case '+':
			for (int i = col - size + 1; i <= col + size + 1; i++) {
				grid[row][i] = '\0';
				centers[row][i][0] = 0;
				centers[row][i][1] = 0;
				centers[row][i][2] = 0;
			}
			for (int i = row - size + 1; i <= row + size + 1; i++) {
				grid[i][col] = '\0';
				centers[row][i][0] = 0;
				centers[row][i][1] = 0;
				centers[row][i][2] = 0;
			}
			temp_row = row;
			temp_col = col;
			
			switch(move_letter) {
				case 'R':
					col += move;
					break;
				case 'L':
					col -= move;
					break;
				case 'U':
					row -= move;
					break;
				case 'D':
					row += move;
					break;
				default:
					return false;
			}
			
			if (col > M - size - 1 || col < size || row > N - size - 1 || row < size) {
				cout << "BORDER ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
				extra_conflict_move(grid, type, row, col, temp_row, temp_col, size);
				pluss(centers, grid, temp_row, temp_col, size);
				return false;
			} else {
				for (int i = col - size + 1; i <= col + size + 1; i++) {
					if (grid[row][i] != '\0') {
						cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
						pluss(centers, grid, temp_row, temp_col, size);
						return false;
					}
				}
				for (int i = row - size + 1; i <= row + size + 1; i++) {
					if (grid[i][col] != '\0') {
						cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
						pluss(centers, grid, temp_row, temp_col, size);
						return false;
					}
				}
				
				pluss(centers, grid, row, col, size);
			}
			cout << "SUCCESS: " << type << " moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
			break;
		case '-':
			for (int i = col - size + 1; i <= col + size + 1; i++) {
				grid[row][i] = '\0';
				centers[row][i][0] = 0;
				centers[row][i][1] = 0;
				centers[row][i][2] = 0;
			}
			temp_row = row;
			temp_col = col;
			
			switch(move_letter) {
				case 'R':
					col += move;
					break;
				case 'L':
					col -= move;
					break;
				case 'U':
					row -= move;
					break;
				case 'D':
					row += move;
					break;
				default:
					return false;
			}
			
			if (col > M - size - 1 || col < size) {
				cout << "BORDER ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
				extra_conflict_move(grid, type, row, col, temp_row, temp_col, size);
				minuss(centers, grid, temp_row, temp_col, size);
				return false;
			} else {
				for (int i = col - size + 1; i <= col + size + 1; i++) {
					if (grid[row][i] != '\0') {
						cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
						minuss(centers, grid, temp_row, temp_col, size);
						return false;
					}
				}
				
				minuss(centers, grid, row, col, size);
			}
			cout << "SUCCESS: " << type << " moved from (" << temp_row << "," << temp_col << ") to (" << row << "," << col << ")." << endl;
			break;
		case 'x':
			for (int i = row - size + 1, j = col - size + 1; i <= row + size + 1 && j <= col + size + 1; i++, j++) {
				grid[i][j] = '\0';
				centers[i][j][0] = 0;
				centers[i][j][1] = 0;
				centers[i][j][2] = 0;
			}
			for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i++, j++) {
				grid[i][j] = '\0';
				centers[i][j][0] = 0;
				centers[i][j][1] = 0;
				centers[i][j][2] = 0;
			}
			temp_row = row;
			temp_col = col;
			
			switch(move_letter) {
				case 'R':
					col += move;
					break;
				case 'L':
					col -= move;
					break;
				case 'U':
					row -= move;
					break;
				case 'D':
					row += move;
					break;
				default:
					return false;
			}
			
			if (col > M - size - 1 || col < size || row > N - size - 1 || row < size) {
				cout << "BORDER ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
				extra_conflict_move(grid, type, row, col, temp_row, temp_col, size);
				crosss(centers, grid, temp_row, temp_col, size);
				return false;
			} else {
				for (int i = row - size + 1, j = col - size + 1; i <= row + size + 1 && j <= col + size + 1; i++, j++) {
					if (grid[i][j] != '\0') {
						cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
						crosss(centers, grid, temp_row, temp_col, size);
						return false;
					}
				}
				
				for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i++, j++) {
					if (grid[i][j] != '\0') {
						cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
						crosss(centers, grid, temp_row, temp_col, size);
						return false;
					}
				}
				
				crosss(centers, grid, row, col, size);
			}
			cout << "SUCCESS: " << type << " moved from (" << temp_row << "," << temp_col << ") to (" << row << "," << col << ")." << endl;
			break;
		case '/':
			for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
				grid[i][j] = '\0';
				centers[i][j][0] = 0;
				centers[i][j][1] = 0;
				centers[i][j][2] = 0;
			}
			temp_row = row;
			temp_col = col;
			
			switch(move_letter) {
				case 'R':
					col += move;
					break;
				case 'L':
					col -= move;
					break;
				case 'U':
					row -= move;
					break;
				case 'D':
					row += move;
					break;
				default:
					return false;
			}
			
			if (col > M - size - 1 || col < size || row > N - size - 1 || row < size) {
				cout << "BORDER ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
				extra_conflict_move(grid, type, row, col, temp_row, temp_col, size);
				slashh(centers, grid, row, col ,size);
				return false;
			} else {
				for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
					if (grid[i][j] != '\0') {
						cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
						slashh(centers, grid, row, col ,size);
						return false;
					}
				}
				
				slashh(centers, grid, row, col, size);
			}
			cout << "SUCCESS: " << type << " moved from (" << temp_row << "," << temp_col << ") to (" << row << "," << col << ")." << endl;
			break;
		default:
			return 1;
	}
	return true;
}

bool extra_conflict_move(char **grid, char type, int row, int col, int temp_row, int temp_col, int size) {
	switch (type) {
		case '+':
			for (int i = col - size + 1; i <= col + size + 1; i++) {
				if (grid[row][i] != '\0') {
					cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			for (int i = row - size + 1; i <= row + size + 1; i++) {
				if (grid[i][col] != '\0') {
					cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		case '-':
			for (int i = col - size + 1; i <= col + size + 1; i++) {
				if (grid[row][i] != '\0') {
					cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		case 'x':
			for (int i = row - size + 1, j = col - size + 1; i <= row + size + 1 && j <= col + size + 1; i++, j++) {
				if (grid[i][j] != '\0') {
					cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size  + 1; i++, j++) {
				if (grid[i][j] != '\0') {
					cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		case '/':
			for (int i = row + size + 1, j = col - size + 1; i <= row - size + 1 && j <= col + size + 1; i--, j++) {
				if (grid[i][j] != '\0') {
					cout << "CONFLICT ERROR: " << type << " can not be moved from (" << temp_row + 1 << "," << temp_col + 1 << ") to (" << row + 1 << "," << col + 1 << ")." << endl;
					return false;
				}
			}
			break;
		default:
			break;
	}
	return true;
}
