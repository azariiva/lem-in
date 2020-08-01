import sys

def show_error_msg(em, n):
	print("Checker: line {}".format(n + 1))
	print("Checker: {}".format(em))

class	Node:
	name : str
	neighbors : list

	def __init__(self, name):
		self.name = str(name)
		self.neighbors = []

	def add_neigbour(self, neighbour):
		self.neighbors.append(neighbour)

	def is_neighbour(self, node):
		for neighbor in self.neighbors:
			if neighbor.name == node.name:
				return True
		return False

class	Lemin:
	name : str
	nodes : list
	ants : dict
	semaphores : list
	start : Node
	end : Node
	num_ants : int
	__sdec__ : bool
	__edec__ : bool

	def __init__(self, name="Graph"):
		self.nodes = []
		self.start = None
		self.end = None
		self.num_ants = 0
		self.__sdec__ = 0
		self.__edec__ = 0
		self.name = name

	def add_node(self, node_name):
		node = Node(node_name)
		if self.__sdec__:
			self.start = node
			self.ants = {i + 1:node for i in range(self.num_ants)}
			self.__sdec__ = False
		elif self.__edec__:
			self.end = node
			self.__edec__ = False
		self.nodes.append(node)

	def find_node(self, node_name):
		for node in self.nodes:
			if node.name == node_name:
				return node
		return None

	def add_link(self, names):
		node_a = None
		node_b = None
		for node in self.nodes:
			if names[0] == node.name:
				node_a = node
			elif names[1] == node.name:
				node_b = node
			if node_a and node_b:
				break
		if not node_a or not node_b:
			return
		node_a.add_neigbour(node_b)
		node_b.add_neigbour(node_a)

	def parse_line(self, line):
		if line == '':
			return
		if line[0] == '#':
			if '##start' in line:
				self.__sdec__ = True
			elif '##end' in line:
				self.__edec__ = True
			else:
				self.__sdec__, self.__edec__ = False, False
		elif line.count(' ') == 2:
			self.add_node(line.split(' ')[0])
		elif '-' in line:
			self.add_link(line.split('-'))

	def read_input(self, argfile):
		n = 0
		num_ant = 0
		for n, line in enumerate(argfile):
			line = line.rstrip('\n')
			if n == 0 and line.isdigit():
				self.num_ants = int(line)
				self.semaphores = [False] * (self.num_ants + 1)
			elif 'L' in line and '-' in line:
				for i in range(self.num_ants + 1):
					self.semaphores[i] = False
				for s in line.split(' '):
					s = s.split('-')
					ant = int(s[0][1:])
					if self.semaphores[ant]:
						show_error_msg("ant number {} making two steps".format(ant), n)
						return
					self.semaphores[ant] = True
					if ant > self.num_ants or ant < 1:
						show_error_msg("ant number {} not valid".format(ant), n)
						return
					node = self.find_node(str(s[1]))
					if not node:
						show_error_msg("room {} not found".format(s[1]), n)
						return
					if not self.ants[ant].is_neighbour(node):
						show_error_msg("no link {}-{}".format(self.ants[ant].name, node.name), n);
						return
					if node in self.ants.values() and node.name != self.end.name:
						show_error_msg("ant is trying to enter room {}, which is busy".format(node.name), n);
						return
					self.ants[ant] = node
				pass
			else:
				self.parse_line(line)
		for ant, node in self.ants.items():
			if node.name != self.end.name:
				print("Checker: ant {} still in room {} after all his journey :(".format(ant, node.name))
				return
		print('Checker: OK')



loops = Lemin()

def	main():
	loops.read_input(sys.stdin)

if __name__ == '__main__':
	main()
