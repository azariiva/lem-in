import sys
import json
import argparse
import contextlib
import pytweening
import time
import networkx as nx
import matplotlib
import matplotlib.pyplot as plt

class	Lemin:

	def __init__(self, name=None):
		self.name = "Graph"
		self.connections = []
		self.nodes = []
		self.start = None
		self.end = None
		self.num_ants = 0
		self.ants = {}
		self.antmoves = []
		self.nodes_colors = []

	def add_room(self, line, start_end):
		self.nodes.append(line)

	def add_edge(self, line):
		self.connections.append(line)

	def add_ant(self, line):
		for move in line.split(" "):
			a = move.split("-")
			if a[0] not in self.ants:
				self.ants[a[0]] = [a[1]]
			else:
				self.ants[a[0]].append(a[1])

	def read_input(self, argfile):
		start_end = 0
		lines = [line.rstrip("\n") for line in argfile]

		n = 0
		tmp_list = []
		num_ant = 0
		for line in lines:
			if line == "":
				pass
			elif n == 0 and line.isdigit():
				self.num_ants = int(line)
			elif line[0] == '#':
				if line == "##start":
					start_end = 1
				elif line == "##end":
					start_end = -1
				else:
					start_end = 0
			elif line.count(" ") == 2:
				self.add_room(line, start_end)
			elif "L" not in line and "-" in line:
				self.add_edge(line)
			elif "L" in line and "-" in line:
				self.antmoves.append(line)
				self.add_ant(line)
				str_h = line.split(" ")
				tmp_list.clear()
				for s in str_h:
					tmp_list.append(s.split("-")[1])
				i = 0
				while (i < len(tmp_list)):
					j = i + 1
					while (j < len(tmp_list)):
						if (tmp_list[i] == tmp_list[j] and tmp_list[i] != self.end and tmp_list[j] != self.end):
							print("LINE: ", tmp_list)
							print("Checker: Oops!: {}=={}".format(tmp_list[i], tmp_list[j]), "in line {}".format(n + 1))
							return
						j += 1
					if (tmp_list[i] == self.end):
						num_ant += 1
					i += 1
			n += 1
		if (self.ants == num_ant):
			print("Checker: OK")
		else:
			print("Checker: Oops!: Num of ants: {}, but you're result: {}".format(self.num_ants, num_ant))

loops = Lemin()

def	main():
	loops.read_input(sys.stdin)

if __name__ == '__main__':
	main()
