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
		self.antmoves = []
		self.nodes_colors = []

	def read_input(self, argfile):
		start_end = 0
		n = 0
		num_ant = 0
		ants=[]
		for line in argfile:
			line = line.rstrip('\n')
			if line == '':
				continue
			if n == 0 and line.isdigit():
				self.num_ants = int(line)
			elif line[0] == '#':
				if '##start' in line:
					start_end = 1
				if '##end' in line:
					start_end = -1
				else:
					start_end = 0
			if "L" in line and "-" in line:
				tmp_list = [s.split("-") for s in line.split(" ")]
				i = 0
				while (i < len(tmp_list)):
					j = i + 1
					while (j < len(tmp_list)):
						if tmp_list[i][1] == tmp_list[j][1] and tmp_list[i][1] != self.end and tmp_list[j][1] != self.end:
							print("LINE: ", tmp_list)
							print("Checker: Oops!: {} == {} in line {}".format(tmp_list[i], tmp_list[j], n + 1))
							return
						elif tmp_list[i][0] == tmp_list[j][0]:
							print("LINE: ", tmp_list)
							print("Checker: Oops!: one ant two rooms in line {}".format(n + 1))
							return
						j += 1
					if tmp_list[i][1] == self.end:
						ants.append(int(tmp_list[i][0][1:]))
						num_ant += 1
					i += 1
			elif line.count(" ") == 2:
				if start_end == 1:
					self.start = line.split(' ')[0]
				elif start_end == -1:
					self.end = line.split(' ')[0]
				else:
					self.nodes.append(line.split(' ')[0])
				start_end = 0
			n += 1
		if self.num_ants == num_ant:
			print("Checker: OK")
		else:
			print("Checker: Oops!: Num of ants: {}, but you're result: {}".format(self.num_ants, num_ant))
			for i in range(self.num_ants):
				if i + 1 not in ants:
					print("no ant {}".format(i + 1))


loops = Lemin()

def	main():
	loops.read_input(sys.stdin)

if __name__ == '__main__':
	main()
