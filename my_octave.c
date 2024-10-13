//Postelnicu Cristina-Marina 313CA
#include <stdio.h>
#include <stdlib.h>

void add_matrix(int ****v, int *poz, int *maxsize, int **vm, int **vn);
int  **read_matrix(int *m, int *n);
void print_matrix(int **vm, int **vn, int ****a, int *poz);
void redimensionare_matrix(int ****v, int **vm, int **vn, int *poz);
int **multiply1(int ****v, int **vm, int **vn, int poz1, int poz2);
void add_m_matrix(int ****v, int **vm, int **vn, int *poz, int *maxsize);
int suma_elem(int **a, int m, int n);
void sort_matrix(int ****v, int **vm, int **vn, int *poz);
void transpunere_matrix(int ****v, int **vm, int **vn, int *poz);
int **multiply2(int n, int m, int p, int **a, int **b, int **c);
void ridicare_matrix(int ****v, int **vm, int **vn, int *poz);
void free_matrix(int ****v, int **vm, int **vn, int *poz);
void free_resources(int ****v, int **vm, int **vn, int *poz);

//functia add_matrix adauga matricele citite la comanda L in vectorul de matrice
void add_matrix(int ****v, int *poz, int *maxsize, int **vm, int **vn)
{
	int m, n;
	if (*poz >= *maxsize) {
		/*realocam memorie pentru vectorul de matrice atunci cand numarul
		matricei depaseste numarul maxim de matrice*/
		*v = realloc(*v, 2 * (*maxsize) * sizeof(int **));
		if (!*v) {
			printf("Alocarea nu a reusit");
			free(*v);
			*v = NULL;
		}
		/*realocam memorie pentru vectorul care contine numarul de linii
		al fiecarei matrice din vector*/
		*vm = realloc(*vm, 2 * (*maxsize) * sizeof(int));
		if (!*vm) {
			printf("Alocarea nu a reusit");
			free(*vm);
			*vm = NULL;
		}
		/*realocam memorie pentru vectorul care contine numarul de coloane
		al fiecarei matrice din vector*/
		*vn = realloc(*vn, 2 * (*maxsize) * sizeof(int));
		if (!*vn) {
			printf("Alocarea nu a reusit");
			free(*vn);
			*vn = NULL;
		}
		//dublam capacitatea vectorului
		*maxsize = (*maxsize) * 2;
	}
	//apelam functia de alocare si de citire pentru o matrice din vector
	int **a = read_matrix(&m, &n);
	/*adaugam matricea alocata si citita in vector, cat si liniile
	si coloanele acesteia in vectorii corespunzatori*/
	(*v)[*poz] = a;
	(*vm)[*poz] = m;
	(*vn)[*poz] = n;
	(*poz)++;
}

//functia read_matrix returneaza o matrice alocata dinamic si citita
int **read_matrix(int *m, int *n)
{
	int i, j;
	scanf("%d %d", m, n);
	//alocam matricea si verificam daca alocarea a reusit
	int **a = malloc(*m * sizeof(int *));
	if (!a) {
		printf("Alocarea nu a reusit");
		a = NULL;
	}
	for (i = 0; i < *m; i++) {
		a[i] = malloc(*n * sizeof(int));
		if (!a[i]) {
			printf("Alocarea nu a reusit");
			for (j = 0; j < i; j++)
				free(a[j]);
			free(a);
			a = NULL;
		}
	}
	//citim matricea
	for (i = 0; i < *m; i++) {
		for (j = 0; j < *n; j++)
			scanf("%d", &a[i][j]);
	}
	//returnam matricea
	return a;
}

//functia print_matrix printeaza matricea ceruta prin comanda P
void print_matrix(int **vm, int **vn, int ****a, int *poz)
{
	int i, j, index;
	//citim indexul matricei pe care dorim sa o printam
	scanf("%d", &index);
	/*verificam daca indexul este pozitiv si mai mic decat numarul
	total de matrice*/
	if (index >= 0 && index < *poz) {
		for (i = 0; i < (*vm)[index]; i++) {
			for (j = 0; j < (*vn)[index]; j++)
				printf("%d ", (*a)[index][i][j]);
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
}

/*functia redimensionare_matrix redimensioneaza in place matricea ceruta
prin comanda C*/
void redimensionare_matrix(int ****v, int **vm, int **vn, int *poz)
{
	int i, j, index, l, c;
	//citim indexul matricei pe care dorim sa o printam
	scanf("%d", &index);
	//citim numarul de linii al matricei redimensionate
	scanf("%d", &l);
	//alocam memorie pentru vectorul liniilor
	int *lin = malloc(l * sizeof(int));
	if (!lin) {
		printf("Alocarea nu a reusit");
		free(lin);
		lin = NULL;
	}
	//citim liniile pe care pe pastram din matrice
	for (i = 0; i < l; i++)
		scanf("%d", &lin[i]);
	//citim numarul de coloane al matricei redimensionate
	scanf("%d", &c);
	//alocam memorie pentru vectorul coloanelor
	int *col = malloc(c * sizeof(int));
	if (!col) {
		printf("Alocarea nu a reusit");
		free(col);
		col = NULL;
	}
	//citim coloanele pe care pe pastram din matrice
	for (i = 0; i < c; i++)
		scanf("%d", &col[i]);
	if (index < 0 || index >= *poz) {
		printf("No matrix with the given index\n");
	} else {
		//alocam memorie pentru noua matrice
		int **r = malloc(l * sizeof(int *));
		if (!r) {
			printf("Alocarea nu a reusit\n");
			r = NULL;
			free(lin);
			free(col);
		}
		for (i = 0; i < l; i++) {
			r[i] = malloc(c * sizeof(int));
			if (!r[i]) {
				printf("Alocarea nu a reusit\n");
				for (j = 0; j < i; j++)
					free(r[j]);
				free(r);
		}
		}
		/*intersectam liniile si coloanle date pentru
		a forma noua matrice*/
		for (i = 0; i < l; i++) {
			for (j = 0; j < c; j++)
				r[i][j] = (*v)[index][lin[i]][col[j]];
		}
		for (i = 0; i < (*vm)[index]; i++)
			free((*v)[index][i]);
		free((*v)[index]);
		//matricea initiala devine matricea redimensionata
		(*v)[index] = r;
		//actualizam numarul de linii al matricei redimensionate
		(*vm)[index] = l;
		//analog pentru coloane
		(*vn)[index] = c;
	}
	free(lin);
	free(col);
}

//functia multiply1 inumulteste 2 matrice cu indexul dat din vector
int **multiply1(int ****v, int **vm, int **vn, int poz1, int poz2)
{
	int i, j, k;
	//alocam memorie pentru matricea rezultata din inmultire
	int **m = malloc((*vm)[poz1] * sizeof(int *));
	if (!m) {
		printf("Alocarea nu a reusit\n");
		m = NULL;
	}
	for (i = 0; i < (*vm)[poz1]; i++) {
		m[i] = malloc((*vn)[poz2] * sizeof(int));
		if (!m[i]) {
			printf("Alocarea nu a reusit");
			for (j = 0; j < i; j++)
				free(m[j]);
			free(m);
		m = NULL;
		}
	}
	for (i = 0; i < (*vm)[poz1]; i++)
		for (j = 0; j < (*vn)[poz2]; j++) {
			m[i][j] = 0;//initializam elementele cu 0
			for (k = 0; k < (*vn)[poz1]; k++) {
				m[i][j] += (*v)[poz1][i][k] * (*v)[poz2][k][j];
				m[i][j] = m[i][j] % 10007;
				if (m[i][j] < 0)
					m[i][j] = m[i][j] + 10007;
			}
		}
	return m;//returnam matricea rezultata prin inmultire
}

/*functia add_m_matrix adauga matricea rezultata prin inmultire
in vectorul de matrice*/
void add_m_matrix(int ****v, int **vm, int **vn, int *poz, int *maxsize)
{
	int poz1, poz2;
	scanf("%d %d", &poz1, &poz2);
	if (poz1 < 0 || poz1 > *poz || poz2 < 0 || poz2 > *poz) {
		printf("No matrix with the given index\n");
		//verificam daca dimensiunile matricelor permit inmultirea
	} else if ((*vn)[poz1] != (*vm)[poz2]) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		//apelam functia multiply1 pentru a inmultii matricele
		int **m = multiply1(v, vm, vn, poz1, poz2);
		/*realocam memorie vectorului de matrice pentru
		a adauga la final matricea rezultata*/
		if (*poz >= *maxsize) {
			*v = realloc(*v, 2 * (*maxsize) * sizeof(int **));
			if (!*v) {
				printf("Alocarea nu a reusit");
				free(*v);
				*v = NULL;
			}
			*vm = realloc(*vm, 2 * (*maxsize) * sizeof(int));
			if (!*vm) {
				printf("Alocarea nu a reusit");
				free(*vm);
				*vm = NULL;
			}
			*vn = realloc(*vn, 2 * (*maxsize) * sizeof(int));
			if (!*vn) {
				printf("Alocarea nu a reusit");
				free(*vn);
				*vn = NULL;
			}
			*maxsize = (*maxsize) * 2;
		}
		//punem matricea pe ultima pozitie
		(*v)[*poz] = m;
		//actualizam numarul de linii si de coloane
		(*vm)[*poz] = (*vm)[poz1];
		(*vn)[*poz] = (*vn)[poz2];
		//crestem numarul de matrice
		(*poz)++;
	}
}

//functia sum_elem calculeaza suma elementelor unei matrice
int suma_elem(int **a, int m, int n)
{
	int i, j, s = 0;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			s += a[i][j];
	return s;
}

/*functia sort_matrix sorteaza matricele in functie de suma
elementelor*/
void sort_matrix(int ****v, int **vm, int **vn, int *poz)
{
	//folosim algoritmul bubble_sort
	int i, j, aux_vm = 0, aux_vn = 0, s1 = 0, s2 = 0;
	for (i = 0; i < *poz  - 1; ++i)
		for (j = 0; j < *poz - i - 1; ++j) {
			//calculam suma elementelor matricelor
			s1 = suma_elem((*v)[j], (*vm)[j], (*vn)[j]);
			s1 = s1 % 10007;
			if (s1 < 0)
				s1 = s1 + 10007;
			s2 = suma_elem((*v)[j + 1], (*vm)[j + 1], (*vn)[j + 1]);
			s2 = s2 % 10007;
			if (s2 < 0)
				s2 = s2 + 10007;
			if (s1 > s2) {
				//folosim o matrice auxiliara pentru a permuta matricele
				int **aux_mat = (*v)[j];
				(*v)[j] = (*v)[j + 1];
				(*v)[j + 1] = aux_mat;
				//permutam liniile matricelor in vectorul de linii
				aux_vm = (*vm)[j];
				(*vm)[j] = (*vm)[j + 1];
				(*vm)[j + 1] = aux_vm;
				//permutam coloanele matricelor in vectorul de coloane
				aux_vn = (*vn)[j];
				(*vn)[j] = (*vn)[j + 1];
				(*vn)[j + 1] = aux_vn;
			}
		}
}

/*functia transpunere_matrix transpune in place o matrice
cu indexul dat pentru comanda T*/
void transpunere_matrix(int ****v, int **vm, int **vn, int *poz)
{
	int i, j, index, aux;
	scanf("%d", &index);
	if (index >= 0 && index < *poz) {
		//alocam memorie pentru matricea transpusa
		int **t = malloc((*vn)[index] * sizeof(int *));
		if (!t) {
			printf("Alocarea nu a reusit");
			t = NULL;
		}
		for (i = 0; i < (*vn)[index]; i++) {
			t[i] = malloc((*vm)[index] * sizeof(int));
			if (!t[i]) {
				printf("Alocarea nu a reusit");
				for (j = 0; j < i; j++)
					free(t[j]);
				free(t);
				t = NULL;
			}
		}
		for (i = 0; i < (*vn)[index]; i++)
			for (j = 0; j < (*vm)[index]; j++)
			//schimbam liniile cu coloanele
				t[i][j] = (*v)[index][j][i];

		for (i = 0; i < (*vm)[index]; i++)
			free((*v)[index][i]);
		free((*v)[index]);
		//adaugam matricea transpusa in locul matricei originale din vector
		(*v)[index] = t;
		aux = (*vm)[index];
		(*vm)[index] = (*vn)[index];
		(*vn)[index] = aux;
	} else {
		printf("No matrix with the given index\n");
	}
}

//functia multiply2 inmulteste 2 matrice oarecare
int **multiply2(int n, int m, int p, int **a, int **b, int **c)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			c[i][j] = 0;
			for (int k = 0; k < p; k++) {
				c[i][j] += a[i][k] * b[k][j];
				c[i][j] = c[i][j] % 10007;
				if (c[i][j] < 0)
					c[i][j] = c[i][j] + 10007;
			}
		}
	}
	return c;
}

void ridicare_matrix(int ****v, int **vm, int **vn, int *poz)
{
	int i, j, m, power;
	//citim indexul m al matricei si puterea la care trebuie sa o ridicam
	scanf("%d", &m);
	scanf("%d", &power);
	if (m < 0 || m >= *poz) {
		printf("No matrix with the given index\n");
		//verificam daca puterea este pozitiva
	} else if (power < 0) {
		printf("Power should be positive\n");
	} else if ((*vm)[m] != (*vn)[m]) {
		//verificam daca matricea este patratica
		printf("Cannot perform matrix multiplication\n");
	} else {
		//alocam memorie pentru matricea ridicata la putere
		int **p = malloc((*vm)[m]  * sizeof(int *));
		if (!p) {
			printf("Alocarea nu a reusit");
			p = NULL;
		}
		for (i = 0; i < (*vm)[m]; i++) {
			p[i] = malloc((*vn)[m] * sizeof(int));
			if (!p[i]) {
				printf("Alocarea nu a reusit");
				for (j = 0; j < i; j++)
					free(p[j]);
				free(p);
				p = NULL;
			}
		}
		//initializam matricea p cu In
		for (i = 0; i < (*vm)[m]; i++)
			for (j = 0; j < (*vn)[m]; j++)
				if (i == j)
					p[i][j] = 1;
				else
					p[i][j] = 0;
		while (power != 0) {
			if (power % 2 == 1) {
				/*daca puterea este impara inmultim matricea p cu
				cu matricea care trebuie ridicata la putere*/
				int **p1 = malloc((*vm)[m] * sizeof(int *));
				if (!p1) {
					printf("Alocarea nu a reusit\n");
					p1 = NULL;
				}
				for (i = 0; i < (*vm)[m]; i++)
					p1[i] = malloc((*vn)[m] * sizeof(int));
				p1 = multiply2((*vm)[m], (*vn)[m], (*vn)[m], p, (*v)[m], p1);
				for (i = 0; i < (*vm)[m]; i++)
					free(p[i]);
				free(p);
				//actualizam p cu rezultatul acestei inmultiri
				p = p1;
			}
			//daca puterea este para efectuam inmultirea matricei cu ea insasi
			//folosim functia multiply1 deoarece cunoastem indexul
			int **aux = multiply1(v, vm, vn, m, m);
			for (i = 0; i < (*vm)[m]; i++)
				free((*v)[m][i]);
			free((*v)[m]);
			//patratul matricei ii ia locul in vector
			(*v)[m] = aux;
			//micsoram puterea pana cand aceasta va deveni 0
			power /= 2;
		}
		for (i = 0; i < (*vm)[m]; i++)
			free((*v)[m][i]);
		free((*v)[m]);
		//matricea se transforma in ridicarea acesteia la putere
		(*v)[m] = p;
	}
}

/*functia free_matrix elibereaza memoria pentru o matrice
cu indexul dat pentru comanda F*/
void free_matrix(int ****v, int **vm, int **vn, int *poz)
{
	int i, index;
	scanf("%d", &index);
	if (!(index >= 0 && index < *poz)) {
		printf("No matrix with the given index\n");
	} else {
		//eliberam matricea
		for (i = 0; i < (*vm)[index]; i++)
			free((*v)[index][i]);
		free((*v)[index]);
		for (i = index ; i < *poz - 1; i++) {
			//deplasam elementele vectorului la stanga
			(*v)[i] = (*v)[i + 1];
			(*vm)[i] = (*vm)[i + 1];
			(*vn)[i] = (*vn)[i + 1];
		}
		//eliberam locul matricei in vectorii corespunzatori
		(*v)[*poz - 1] = NULL;
		(*vm)[*poz - 1] = 0;
		(*vn)[*poz - 1] = 0;
		(*poz)--;
	}
}

//functia free_resources elibereaza memoria alocata pentru vectori
void free_resources(int ****v, int **vm, int **vn, int *poz)
{
	int i, j;
	//eliberam vectorul de matrice
	for (i = 0; i < *poz; i++) {
		for (j = 0; j < (*vm)[i]; j++)
			free((*v)[i][j]);
		free((*v)[i]);
	}
	free(*v);
	//eliberam vectorul liniilor
	free(*vm);
	//eliberam vectorul coloanelor
	free(*vn);
}

int main(void)
{
	char c;
	//citim caracterul pentru comanda pe care o vom da
	scanf(" %c", &c);
	int maxsize = 1, poz = 0, index = 0;
	//alocam memorie pentru un element in vectorul de matrice
	int ***v = malloc(1 * sizeof(int **));
	if (!v) {
		printf("Alocarea nu a reusit");
		free(v);
		v = NULL;
	}
	//alocam memorie pentru un element in vectorul de linii
	int *vm = malloc(1 * sizeof(int));
	if (!vm) {
		printf("Alocarea nu a reusit");
		free(vm);
		vm = NULL;
	}
	//alocam memorie pentru un element in vectorul de coloane
	int *vn = malloc(1 * sizeof(int));
	if (!vn) {
		printf("Alocarea nu a reusit");
		free(vn);
		vn = NULL;
	}
	//comanda Q reprezinta eliberarea tuturor resurselor
	while (c != 'Q') {
		/*folosim switch ul pentru a efectua operatiile corespunzatoare
		in functie de litera introdusa de la tastatura*/
		switch (c) {
		case 'L':
		add_matrix(&v, &poz, &maxsize, &vm, &vn);
		break;
		case 'D':
		scanf("%d", &index);
		if (index < 0 || index >= poz)
			printf("No matrix with the given index\n");
		else
			printf("%d %d\n", vm[index], vn[index]);
		break;
		case 'P':
		print_matrix(&vm, &vn, &v, &poz);
		break;
		case 'C':
		redimensionare_matrix(&v, &vm, &vn, &poz);
		break;
		case 'M':
		add_m_matrix(&v, &vm, &vn, &poz, &maxsize);
		break;
		case 'O':
		sort_matrix(&v, &vm, &vn, &poz);
		break;
		case 'T':
		transpunere_matrix(&v, &vm, &vn, &poz);
		break;
		case 'R':
		ridicare_matrix(&v, &vm, &vn, &poz);
		break;
		case 'F':
		free_matrix(&v, &vm, &vn, &poz);
		break;
		default:
		printf("Unrecognized command\n");
		break;
		}
		scanf("\n");
		//citim o noua litera
		scanf(" %c", &c);
	}
	//eliberam memoria alocata
	free_resources(&v, &vm, &vn, &poz);
	return 0;
}
