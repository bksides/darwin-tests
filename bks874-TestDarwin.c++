// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#define Test_Darwin_cpp

#include "gtest/gtest.h"
#include "Darwin.h"

using namespace std;

// ----
// test
// ----

TEST(test_board, instruction_1)
{
	Instruction i = instructions::hop;
	ASSERT_EQ(i.action, instructions::hop);
}

TEST(test_board, instruction_2)
{
	Instruction i(instructions::go, 0);
	ASSERT_EQ(i.next, 0);
}

TEST(test_board, instruction_3)
{
	Instruction i(instructions::go, 0);
	ASSERT_EQ(i.action, instructions::go);
}

TEST(test_board, instruction_4)
{
	Instruction i = instructions::right;
	ASSERT_EQ(i.next, -1);
}

//Species
TEST(test_board, species_1)
{
	Species s;
	ASSERT_EQ(s.species_symbol, 'X');
}

TEST(test_board, species_2)
{
	Species s;
	ASSERT_EQ(s.program.size(), 0);
}

TEST(test_board, species_3)
{
	Species s = 'C';
	ASSERT_EQ(s.species_symbol, 'C');
}

TEST(test_board, species_4)
{
	Species s = 'C';
	ASSERT_EQ(s.program.size(), 0);
}

TEST(test_board, add_instruction_1)
{
	Species s = 'C';
	s.add_instruction(instructions::hop);
	ASSERT_EQ(s.program.size(), 1);
}

TEST(test_board, add_instruction_2)
{
	Species s = 'C';
	s.add_instruction(instructions::hop);
	ASSERT_EQ(s.program[0].action, instructions::hop);
}

TEST(test_board, add_instruction_3)
{
	Species s = 'C';
	s.add_instruction(instructions::hop);
	ASSERT_EQ(s.program[0].next, -1);
}

TEST(test_board, add_instruction_4)
{
	Species s = 'C';
	s.add_instruction(instructions::go, 1);
	ASSERT_EQ(s.program[0].next, 1);
}

TEST(test_board, get_instruction_1)
{
	Species s = 'C';
	s.add_instruction(instructions::hop);
	ASSERT_EQ(s.getInstruction(0).action, hop);
}

TEST(test_board, get_instruction_2)
{
	Species s = 'C';
	s.add_instruction(instructions::hop);
	ASSERT_EQ(s.getInstruction(0).next, -1);
}

TEST(test_board, getInstruction_3)
{
	Species s = 'C';
	s.add_instruction(instructions::hop);
	s.add_instruction(instructions::go, 0);
	ASSERT_EQ(s.getInstruction(1).action, instructions::go);
}

TEST(test_board, getInstruction_4)
{
	Species s = 'C';
	s.add_instruction(instructions::hop);
	s.add_instruction(instructions::go, 0);
	ASSERT_EQ(s.getInstruction(1).next, 0);
}

TEST(test_board, species_equality_1)
{
	Species s = 'S';
	Species c = 'S';
	ASSERT_TRUE(s == c);
}

TEST(test_board, species_equality_2)
{
	Species s = 'S';
	Species c = 'C';
	ASSERT_FALSE(s == c);
}

TEST(test_board, get_creature_at_1)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 1);
	ASSERT_EQ(b.getCreatureAt(1, 1), &c);
}

TEST(test_board, get_creature_at_2)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 1);
	ASSERT_EQ(b.getCreatureAt(1, 0), nullptr);
}

TEST(test_board, get_creature_at_3)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 2);
	ASSERT_EQ(b.getCreatureAt(1, 2), &c);
}

TEST(test_board, add_creature_1)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 2);
	ASSERT_EQ(b.board[1][2], &c);
}

TEST(test_board, add_creature_2)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 2);
	ASSERT_EQ(c.board, &b);
}

TEST(test_board, add_creature_3)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 2);
	ASSERT_EQ(c.x, 2);
}

TEST(test_board, add_creature_4)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 2);
	ASSERT_EQ(c.y, 1);
}

TEST(test_board, add_creature_5)
{
	Board b(3, 3);
	Species s = 'S';
	Creature c = s;
	b.add_creature(&c, 1, 2, north);
	ASSERT_EQ(c.direction, north);
}

TEST(test_board, step_1)
{
	Board b(3, 3);
	Species s = 'S';
	s.add_instruction(instructions::hop);
	Creature c = s;
	b.add_creature(&c, 1, 1, north);
	b.step();
	ASSERT_EQ(&c, b.getCreatureAt(0, 1));
}

TEST(test_board, step_2)
{
	Board b(3, 3);
	Species s = 'S';
	s.add_instruction(instructions::hop);
	Creature c1 = s;
	Creature c2 = s;
	b.add_creature(&c1, 1, 0, north);
	b.add_creature(&c2, 1, 2, south);
	b.step();
	ASSERT_EQ(&c2, b.getCreatureAt(2, 2));
}

TEST(test_board, step_3)
{
	Board b(5, 5);
	Species s = 'S';
	s.add_instruction(instructions::hop);
	Creature c = s;
	b.add_creature(&c, 0, 0, east);
	b.step();
	ASSERT_EQ(&c, b.getCreatureAt(0, 1));
}

TEST(test_board, board_1)
{
	Board b(5, 7);
	ASSERT_EQ(b.sizex, 7);
}

TEST(test_board, board_2)
{
	Board b(5, 7);
	ASSERT_EQ(b.sizey, 5);
}

TEST(test_board, board_3)
{
	Board b(5, 7);
	ASSERT_EQ(b.board.size(), 5);
}

TEST(test_board, board_4)
{
	Board b(5, 7);
	ASSERT_EQ(b.board[1].size(), 7);
}

TEST(test_board, done_1)
{
	Board b(5,5);
	ASSERT_TRUE(b.done());
}

TEST(test_board, done_2)
{
	Board b(5,5);
	Species s = 'C';
	Creature c = s;
	b.add_creature(&c, 2, 2);
	ASSERT_TRUE(b.done());
}

TEST(test_board, done_3)
{
	Board b(5,5);
	Species s = 'C';
	Creature c1 = s;
	Creature c2 = s;
	b.add_creature(&c1, 2, 2);
	b.add_creature(&c2, 1, 1);
	ASSERT_TRUE(b.done());
}

TEST(test_board, done_4)
{
	Board b(5,5);
	Species s1 = 'C';
	Species s2 = 'S';
	Creature c1 = s1;
	Creature c2 = s2;
	b.add_creature(&c1, 2, 2);
	b.add_creature(&c2, 1, 1);
	ASSERT_FALSE(b.done());
}

TEST(test_board, print_1)
{
	ostringstream s("");
	Board b(5,5);
	b.print(s);
	ASSERT_EQ(s.str(), "0 .....\n1 .....\n2 .....\n3 .....\n4 .....\n");
}

TEST(test_board, print_2)
{
	ostringstream s("");
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	b.print(s);
	ASSERT_EQ(s.str(), "0 .....\n1 .....\n2 ..S..\n3 .....\n4 .....\n");
}

TEST(test_board, print_3)
{
	ostringstream s("");
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::hop);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	b.step();
	b.print(s);
	ASSERT_EQ(s.str(), "0 .....\n1 ..S..\n2 .....\n3 .....\n4 .....\n");
}

TEST(test_board, exec_1)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::hop);
	sp.add_instruction(instructions::go, 0);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.exec();
	ASSERT_EQ(c.program_counter, 1);
}

TEST(test_board, exec_2)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::hop);
	sp.add_instruction(instructions::go, 0);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.exec();
	c.exec();
	ASSERT_EQ(c.y, 0);
}

TEST(test_board, exec_3)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::go, 7);
	sp.add_instruction(instructions::hop);
	sp.add_instruction(instructions::go, 1);
	sp.add_instruction(instructions::go, 2);
	sp.add_instruction(instructions::go, 3);
	sp.add_instruction(instructions::go, 8);
	sp.add_instruction(instructions::go, 4);
	sp.add_instruction(instructions::go, 5);
	sp.add_instruction(instructions::go, 6);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.exec();
	ASSERT_EQ(c.y, 1);
}

TEST(test_board, exec_4)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::left);
	sp.add_instruction(instructions::go, 0);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.exec();
	ASSERT_EQ(c.direction, directions::west);
}

TEST(test_board, exec_5)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::right);
	sp.add_instruction(instructions::go, 0);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.exec();
	ASSERT_EQ(c.direction, directions::east);
}

TEST(test_board, exec_6)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::infect);
	sp.add_instruction(instructions::go, 0);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.exec();
	ASSERT_EQ(c.program_counter, 1);
}

TEST(test_board, exec_7)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::if_empty, 2);
	sp.add_instruction(instructions::hop);
	sp.add_instruction(instructions::hop);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.exec();
	ASSERT_EQ(c.program_counter, 3);
}

TEST(test_board, exec_8)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::if_wall, 2);
	sp.add_instruction(instructions::hop);
	sp.add_instruction(instructions::hop);
	Creature c = sp;
	b.add_creature(&c, 0, 2);
	c.exec();
	ASSERT_EQ(c.program_counter, 3);
}

TEST(test_board, exec_9)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::if_random, 1);
	sp.add_instruction(instructions::hop);
	sp.add_instruction(instructions::hop);
	Creature c = sp;
	b.add_creature(&c, 0, 2);
	c.exec();
	ASSERT_TRUE(c.program_counter == 2);
}

TEST(test_board, exec_10)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::if_enemy, 2);
	sp.add_instruction(instructions::hop);
	sp.add_instruction(instructions::hop);
	Species sp2 = 'C';
	Creature c = sp;
	Creature s = sp2;
	b.add_creature(&c, 2, 2);
	b.add_creature(&s, 1, 2);
	c.exec();
	ASSERT_EQ(c.program_counter, 3);
}

TEST(test_board, hop_1)
{
	Board b(5,5);
	Species sp = 'S';
	sp.add_instruction(instructions::hop);
	Creature c = sp;
	b.add_creature(&c, 2, 2);
	c.hop();
	ASSERT_EQ(c.y, 1);
}

TEST(test_board, hop_2)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2, directions::east);
	c.hop();
	ASSERT_EQ(c.x, 3);
}

TEST(test_board, hop_3)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 4, directions::east);
	c.hop();
	ASSERT_EQ(c.x, 4);
}

TEST(test_board, hop_4)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	Creature d = sp;
	b.add_creature(&c, 2, 2, directions::east);
	b.add_creature(&d, 2, 3);
	c.hop();
	ASSERT_EQ(c.x, 2);
}

TEST(test_board, left_1)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2, directions::east);
	c.left();
	ASSERT_EQ(c.direction, directions::north);
}

TEST(test_board, left_2)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2, directions::east);
	c.left();
	c.left();
	c.left();
	c.left();
	ASSERT_EQ(c.direction, directions::east);
}

TEST(test_board, left_3)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2, directions::east);
	c.left();
	c.hop();
	ASSERT_EQ(c.y, 1);
}

TEST(test_board, right_1)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2, directions::east);
	c.right();
	ASSERT_EQ(c.direction, directions::south);
}

TEST(test_board, right_2)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2, directions::east);
	c.right();
	c.right();
	c.right();
	c.right();
	ASSERT_EQ(c.direction, directions::east);
}

TEST(test_board, right_3)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	b.add_creature(&c, 2, 2, directions::east);
	c.right();
	c.hop();
	ASSERT_EQ(c.y, 3);
}

TEST(test_board, infect_1)
{
	Board b(5,5);
	Species sp = 'S';
	Creature c = sp;
	Creature d = sp;
	d.program_counter = 3;
	b.add_creature(&c, 2, 2, directions::east);
	b.add_creature(&d, 2, 3);
	c.infect();
	ASSERT_EQ(d.program_counter, 3);
}

TEST(test_board, infect_2)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2, directions::east);
	b.add_creature(&c, 2, 3);
	s.infect();
	ASSERT_EQ(c.species, s.species);
}

TEST(test_board, infect_3)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	c.program_counter = 3;
	b.add_creature(&s, 2, 2, directions::east);
	b.add_creature(&c, 2, 3);
	s.infect();
	ASSERT_EQ(c.program_counter, 0);
}

TEST(test_board, infect_4)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2);
	b.add_creature(&c, 2, 3);
	s.infect();
	ASSERT_EQ(c.species, &s2);
}

TEST(test_board, if_empty_1)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2, directions::east);
	b.add_creature(&c, 2, 3);
	s.if_empty(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_empty_2)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 2, directions::east);
	s.if_empty(4);
	ASSERT_EQ(s.program_counter, 4);
}

TEST(test_board, if_empty_3)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4, directions::east);
	s.if_empty(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_empty_4)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4);
	s.if_empty(4);
	ASSERT_EQ(s.program_counter, 4);
}

TEST(test_board, if_empty_5)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2);
	b.add_creature(&c, 2, 3);
	s.if_empty(4);
	ASSERT_EQ(s.program_counter, 4);
}

TEST(test_board, if_wall_1)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2, directions::east);
	b.add_creature(&c, 2, 3);
	s.if_wall(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_wall_2)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 2, directions::east);
	s.if_wall(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_wall_3)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4, directions::east);
	s.if_wall(4);
	ASSERT_EQ(s.program_counter, 4);
}

TEST(test_board, if_wall_4)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4);
	s.if_wall(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_wall_5)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2);
	b.add_creature(&c, 2, 3);
	s.if_wall(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_random_1)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4);
	s.if_random(4);
	ASSERT_TRUE(s.program_counter == 0 || s.program_counter == 4);
}

TEST(test_board, if_enemy_1)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2, directions::east);
	b.add_creature(&c, 2, 3);
	s.if_enemy(4);
	ASSERT_EQ(s.program_counter, 4);
}

TEST(test_board, if_enemy_2)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 2, directions::east);
	s.if_enemy(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_enemy_3)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4, directions::east);
	s.if_enemy(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_enemy_4)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4);
	s.if_enemy(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_enemy_5)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature s = s1;
	Creature c = s2;
	b.add_creature(&s, 2, 2);
	b.add_creature(&c, 2, 3);
	s.if_enemy(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, if_enemy_6)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	Creature c = s1;
	b.add_creature(&s, 2, 2, directions::east);
	b.add_creature(&c, 2, 3);
	s.if_enemy(4);
	ASSERT_EQ(s.program_counter, 0);
}

TEST(test_board, go_1)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature s = s1;
	b.add_creature(&s, 2, 4);
	s.go(4);
	ASSERT_EQ(s.program_counter, 4);
}

TEST(test_board, speciate_1)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature c = s1;
	b.add_creature(&c, 2, 2);
	c.speciate(&s2);
	ASSERT_EQ(c.species, &s2);
}

TEST(test_board, speciate_2)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature c = s1;
	c.program_counter = 3;
	b.add_creature(&c, 2, 2);
	c.speciate(&s2);
	ASSERT_EQ(c.program_counter, 0);
}

TEST(test_board, speciate_3)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature c = s1;
	c.program_counter = 3;
	b.add_creature(&c, 2, 2);
	c.speciate(&s1);
	ASSERT_EQ(c.program_counter, 0);
}

TEST(test_board, is_1)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature c = s1;
	b.add_creature(&c, 2, 2);
	c.speciate(&s2);
	ASSERT_TRUE(c.is(&s2));
}

TEST(test_board, is_2)
{
	Board b(5,5);
	Species s1 = 'S';
	Creature c = s1;
	b.add_creature(&c, 2, 2);
	ASSERT_TRUE(c.is(&s1));
}

TEST(test_board, is_3)
{
	Board b(5,5);
	Species s1 = 'S';
	Species s2 = 'C';
	Creature c = s1;
	b.add_creature(&c, 2, 2);
	ASSERT_FALSE(c.is(&s2));
}