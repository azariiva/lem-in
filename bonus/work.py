#!/Users/blinnea/.brew/bin/python3

import sys
import json
import argparse
import contextlib
import pytweening
import time
import networkx as nx
import matplotlib
import matplotlib.pyplot as plt
#
import matplotlib.animation as animation

col_path = ['orange', 'magenta', 'cyan', 'brown', 'blue', '#f08c00', '#308bc0',
			'#f9c030', '#23f012', '#497663', '#ec5952', '#db8fb0', '#afc58c',
			'#08ea07', '#3e60f3', '#9d5d80', '#701488', '#a78923', '#d461f8',
			'#0628c4', '#2f8bdc', '#1abf73', '#04edc1', '#dffe5d', '#fbfbad',
			'#b26258', '#d2881e', '#95d6ae']

class	Lemin:
	nodes_light = []

	def __init__(self, name=None, G=None, debug=None, pos=None):
		self.name = "Graph"
		self.G = nx.Graph(name=self.name)
		self.draw_grey = False
		self.debug = 0
		self.pos = "kamada"
		self.connections = []
		self.nodes = []
		self.start = None
		self.end = None
		self.num_ants = 0
		self.max_moves = None
		self.max_flow = None
		self.ants = {}
		self.antmoves = []
		self.paths = []
		self.nodes_colors = []
		self.edges_colors = []

	def add_room(self, line, start_end):
		self.nodes.append(line)
		n = line.split(' ')
		if start_end == -1 and 'red' not in self.nodes_colors:
			self.G.add_node(n[0], weight=2)
			self.end = n[0]
			self.nodes_colors.append('red')
		elif start_end == 1 and 'green' not in self.nodes_colors:
			self.G.add_node(n[0], weight=2)
			self.start = n[0]
			self.nodes_colors.append('green')
		else:
			self.G.add_node(n[0], weight=1)
			self.nodes_colors.append('grey')

	def add_edge(self, line):
		self.connections.append(line)
		n = line.split('-')
		self.G.add_edge(n[0], n[1], capacity=1, weight=1)
		self.edges_colors.append("grey")

	def add_ant(self, line):
		for move in line.split(" "):
			a = move.split("-")
			if a[0] not in self.ants:
				self.ants[a[0]] = [a[1]]
			else:
				self.ants[a[0]].append(a[1])

	def draw_graph(self, pos):
		draw_graph_nodes(self.G, self.paths, pos, col_path, self.draw_grey)
		draw_graph_edges(self.G, self.paths, pos, col_path, self.draw_grey)
		plt.axis('off')
		plt.ion()
		plt.show()
		animate(self, pos)

	def read_input(self, argfile):
		start_end = 0
		lines = [line.rstrip("\n") for line in argfile]
		num_lines = len(lines)
		if self.debug >= 2:
			print("num_lines: " + str(num_lines))
		n = 0

		tmp_list = []

		for line in lines:
			if line == "":
				pass
			elif n == 0 and line.isdigit():
				self.num_ants = int(line)
				print("num_ants: " + str(self.num_ants))
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
				for s in str_h:
					tmp_list.append(s.split("-")[1])
				self.nodes_light.append(list(tmp_list))
				tmp_list.clear()
			n += 1

		tmp = []

		if (len(self.antmoves) > 0):
			for move in self.antmoves[0].split(" "):
				tmp.append(move.split("-")[0])

		self.paths.append([self.start, self.end])
		for ant in tmp:
			self.paths.append(self.ants[ant][:-1])
		pos = nx.kamada_kawai_layout(self.G)
		self.draw_graph(pos)

def animate(self, pos):
	for it_nodes in self.nodes_light:
			#изменение цвета
		nx.draw_networkx_nodes(self.G, pos, it_nodes,
									node_color='black', node_size=5)

		if self.G.number_of_nodes() > 50:
			plt.pause(0.1)
		elif self.G.number_of_nodes() > 25:
			plt.pause(0.5)
		else:
			plt.pause(1)
		nx.draw_networkx_nodes(self.G, pos, it_nodes,
									node_color='white', node_size=5)

def draw_graph_nodes(G, paths, pos, col_path, draw_grey):
	n = 0
	flag = False
	for node in G.nodes:
		if node == paths[0][0]:
			nx.draw_networkx_nodes(G, pos, nodelist=[node],
								   node_color='green', node_size=50)
			nx.draw_networkx_nodes(G, pos, nodelist=[node],
								   node_color='white', node_size=5)
		elif node == paths[0][1]:
			nx.draw_networkx_nodes(G, pos, nodelist=[node],
								   node_color='red', node_size=50)
			nx.draw_networkx_nodes(G, pos, nodelist=[node],
								   node_color='white', node_size=5)
		for i in range(1, len(paths)):
			if node in paths[i]:
				nx.draw_networkx_nodes(G, pos, nodelist=[node],
									   node_color=col_path[i + 1], node_size=20)
				nx.draw_networkx_nodes(G, pos, nodelist=[node],
									   node_color='white', node_size=5)
				flag = False
				break
			else:
				flag = True
		# nx.draw_networkx_nodes(G, pos, nodelist=[node],
		# 							   node_color='white', node_size=20)
		if flag and draw_grey:
			nx.draw_networkx_nodes(G, pos, nodelist=[node],
								   node_color=col_path[-1],
								   node_size=2, alpha=0.1)
		flag = False
		n += 1
		if n == len(G.nodes):
			break


def draw_graph_edges(G, paths, pos, col_path, draw_grey):
	e = 0
	flag = False
	for edge in G.edges:
		for i in range(1, len(paths)):
			if (
					(edge[0] in paths[i] and edge[1] in paths[i])
					or (edge[0] in paths[0] and edge[1] in paths[i])
					or (edge[0] in paths[i] and edge[1] in paths[0])
			):
				nx.draw_networkx_edges(G, pos, edgelist=[edge],
									   edge_color=col_path[i+1])
				flag = False
				break
			else:
				flag = True
		if flag and draw_grey:
			nx.draw_networkx_edges(G, pos, edgelist=[edge],
								   edge_color=col_path[-1], alpha=0.1)
		flag = False
		e += 1
		if e == len(G.edges):
			break

def	main():
	loops = Lemin()
	loops.read_input(sys.stdin)

if __name__ == '__main__':
	main()
