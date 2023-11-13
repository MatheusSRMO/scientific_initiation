import numpy as np

class FileHandler(object):

	def __init__(self, filename):
		self.f = open(filename)
		self.A = None
		self.c = None
		self.m = 0
		self.n = 0

	def process(self):
		self.__init_matrix()
		self.__create_cost_vector()
		self.__create_matrix()

		self.f.close()
		return self.A, self.c

	def __init_matrix(self):
		m, n = self.f.readline().split()
		self.m, self.n = int(m), int(n)
		self.A = np.zeros((self.m, self.n))
		self.c = np.zeros(self.n)

	def __create_cost_vector(self):
		nums = []
		while len(nums) < self.n:
			data = self.f.readline().split()
			nums += data
		self.c = np.array(nums).astype(float)

	def __create_matrix(self):
		row = 0
		while row < self.m:
			n = int(self.f.readline())
			row_idx = []
			while len(row_idx) < n:
				data = self.f.readline().split()
				row_idx += data
			row_idx = np.array(row_idx).astype(int) - 1
			self.A[row][row_idx] = 1
			row += 1

	def write_file(self, path_name):
		"""
		Formato do arquivo:
		n m // n = número de linhas, m = número de colunas
		a11 a12 a13 ... a1m
		a21 a22 a23 ... a2m
		a31 a32 a33 ... a3m
		...
		an1 an2 an3 ... anm
    	"""
		f = open(path_name, "w")
		f.write(str(self.n) + " " + str(self.m) + "\n")
		for i in range(self.m):
			row = self.A[i]
			row = row.astype(int)
			row = row.astype(str)
			row = " ".join(row)
			f.write(row + "\n")
		f.close()