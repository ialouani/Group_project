WIDTH ?= 40
HEIGHT ?= 30
CFLAGS = -std=c99 
SANDWICH_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)




all:project
project: rule4.o code_queue4.o projet4.o 
	gcc $(CFLAGS) $(SANDWICH_FLAGS) rule4.o code_queue4.o projet4.o -o project
projet4.o: src/project.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) -c src/project.c -o projet4.o
code_queue4.o: src/code_queue.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) -c src/code_queue.c -o code_queue4.o
rule4.o: src/rule.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) -c src/rule.c -o rule4.o





project2: projet.o code_queue.o rule.o
	gcc -o project2 projet.o code_queue.o rule.o
project_1: src/projet2_test1.c src/rule.c src/code_queue.c
	gcc -std=c99 src/projet2_test1.c src/rule.c src/code_queue.c -o project_1




project_all: test44 project22 test_4_ptrs_fonctions2 project_11 project_1__22 test_achiev22 test_achiev33 test_sable_tombe_v11 test_avance_22 test_presque_final33 test_primaire_g2 test_g_33 test_final2 




projet.o: src/project.c
	gcc $(CFLAGS) -c src/project.c -o projet.o
code_queue.o: src/code_queue.c
	gcc $(CFLAGS) -c src/code_queue.c
rule.o: src/rule.c
	gcc $(CFLAGS) -c src/rule.c
project22: projet.o code_queue.o rule.o
	gcc -o project22 projet.o code_queue.o rule.o
rule3.o: src/rule3.c
	gcc $(CFLAGS) -c src/rule3.c
code_queue3.o: src/code_queue3.c
	gcc $(CFLAGS) -c src/code_queue3.c
test44: projet.o code_queue.o rule.o
	gcc -std=c99 -DHEIGHT=40 -DWIDTH=40 projet.o code_queue.o rule.o -o test44
jeu_vie.o: src/jeu_vie.c
	gcc $(CFLAGS) -c src/jeu_vie.c
test_4_ptrs_fonctions2: rule3.o code_queue3.o jeu_vie.o
	gcc -std=c99 $(SANDWICH_FLAGS) rule3.o code_queue3.o jeu_vie.o -o test_4_ptrs_fonctions2
projet2_test1.o: src/projet2_test1.c
	gcc $(CFLAGS) -c src/projet2_test1.c
project_11: projet2_test1.o rule.o code_queue.o
	gcc -std=c99 projet2_test1.o rule.o code_queue.o -o project_11
projet2_test1_with_animation.o: src/projet2_test1_with_animation.c
	gcc $(CFLAGS) -c src/projet2_test1_with_animation.c
project_1__22: rule.o code_queue.o projet2_test1_with_animation.o
	gcc $(CFLAGS) $(SANDWICH_FLAGS) rule.o code_queue.o projet2_test1_with_animation.o -o project_1__22
test_3_3.o: test/test_3_3.c 
	gcc $(CFLAGS) -c test/test_3_3.c
algo_iteration1.o: src/algo_iteration1.c
	gcc $(CFLAGS) -c src/algo_iteration1.c
test_3_4.o: test/test_3_4.c 
	gcc $(CFLAGS) -c test/test_3_4.c
algo_iteration21.o: src/algo_iteration21.c
	gcc $(CFLAGS) -c src/algo_iteration21.c
test_achiev22: rule3.o code_queue3.o test_3_3.o algo_iteration1.o
	gcc  -std=c99 -DHEIGHT=30 -DWIDTH=30 rule3.o code_queue3.o test_3_3.o algo_iteration1.o -o test_achiev22
test_achiev33: rule3.o code_queue3.o test_3_4.o algo_iteration21.o
	gcc  -std=c99 -DHEIGHT=30 -DWIDTH=30 rule3.o code_queue3.o test_3_4.o algo_iteration21.o -o test_achiev33
test_jeu_final6.o: src/test_jeu_final6.c
	gcc $(CFLAGS) -c src/test_jeu_final6.c
test_sable_tombe_v11: rule3.o code_queue3.o test_jeu_final6.o
	gcc -std=c99 -DHEIGHT=80 -DWIDTH=80 rule3.o code_queue3.o test_jeu_final6.o -o test_sable_tombe_v11
test_jeu_final3.o: src/test_jeu_final3.c
	gcc $(CFLAGS) -c src/test_jeu_final3.c
test_avance_22: rule3.o code_queue3.o test_jeu_final3.o
	gcc -std=c99 -DHEIGHT=100 -DWIDTH=100 rule3.o code_queue3.o test_jeu_final3.o -o test_avance_22
algo_iteration2.o: src/algo_iteration2.c
	gcc $(CFLAGS) -c src/algo_iteration2.c
test_3_2.o: test/test_3_2.c 
	gcc $(CFLAGS) -c test/test_3_2.c
test_presque_final33 : rule3.o code_queue3.o test_3_2.o algo_iteration2.o
	gcc -std=c99 -DHEIGHT=100 -DWIDTH=100 rule3.o code_queue3.o test_3_2.o algo_iteration2.o -o test_presque_final33
test_3_1.o: test/test_3_1.c 
	gcc $(CFLAGS) -c test/test_3_1.c
test_g_33: rule3.o code_queue3.o algo_iteration2.o test_3_1.o
	gcc -std=c99 -DWIDTH=11 -DHEIGHT=11 test_3_1.o rule3.o code_queue3.o algo_iteration2.o -o test_g_33
test_3_5.o: test/test_3_5.c 
	gcc $(CFLAGS) -c test/test_3_5.c
test_final2:  rule3.o code_queue3.o test_3_5.o algo_iteration21.o
	gcc  -std=c99 -DHEIGHT=30 -DWIDTH=30 rule3.o code_queue3.o test_3_5.o algo_iteration21.o -o test_final2
test_jeu_final4.o: src/test_jeu_final4.c
	gcc $(CFLAGS) -c src/test_jeu_final4.c
test_primaire_g2: rule3.o code_queue3.o test_jeu_final4.o
	gcc -std=c99 -DHEIGHT=11 -DWIDTH=11 rule3.o code_queue3.o test_jeu_final4.o -o test_primaire_g2




simulation: test1 test2 test3 test4
	./test4 -m 250 -s 12345 | ./sdl -m
simulation_non_carre: project2
	./project2 -m 350 -s 324 | ./sdl -m
simulation_non_carre_4: test_4_ptrs_fonctions
	./test_4_ptrs_fonctions -m 500 | ./sdl -m
simulation_non_carre_4__2: ultime_test
	./ultime_test -m 300 -s 123 | ./sdl -M
indeterminisme_triviale_regle: project_1
	./project_1 -m 10 | ./sdl -m
indeterminisme_animation_BR: project_1__2
	./project_1__2 -m 10 -s 130 | ./sdl -M
sable_tombe_v2_1: test_achiev2
	./test_achiev2 -m 60 | ./sdl -m
sable_tombe_v2_2: test_achiev3
	./test_achiev3 -m 60 | ./sdl -m
sable_tombe_v1: test_sable_tombe_v1
	./test_sable_tombe_v1 -m 50 | ./sdl -m
sable_obstacles_gravite: test_avance_2 
	./test_avance_2 -m 600 | ./sdl -m
sable_obstacles_gravite_generalisation3: test_presque_final3
	./test_presque_final3 -m 600 | ./sdl -m
cercle_rayon_variant_suivant2: test_primaire_g
	./test_primaire_g -m 300 | ./sdl -m
cercle_rayon_variant_suivant3: test_g_3 
	./test_g_3 -m 100 | ./sdl -m
reservoir_eau: test_final
	./test_final -m 60 | ./sdl -m




test1: src/rule.c test/test_rule.c
	gcc -std=c99 -DHEIGHT=5 -DWIDTH=5 src/rule.c test/test_rule.c -o test1 
test2: src/rule.c test/test_file.c src/code_queue.c
	gcc -std=c99 -DHEIGHT=3 -DWIDTH=3 src/rule.c test/test_file.c src/code_queue.c -o test2
test3: src/test_final_jeu.c src/rule.c src/code_queue.c
	gcc -std=c99 -DHEIGHT=4 -DWIDTH=4 src/test_final_jeu.c src/rule.c src/code_queue.c -o test3
test4: src/project.c src/rule.c src/code_queue.c
	gcc -std=c99 -DHEIGHT=40 -DWIDTH=40 src/project.c src/rule.c src/code_queue.c -o test4

test1_2: src/rule2.c test/test_rule2.c
	gcc -std=c99 src/rule2.c test/test_rule2.c -o test1_2
test2_2: src/rule2.c test/test_file2.c src/code_queue2.c
	gcc -std=c99 src/rule2.c test/test_file2.c src/code_queue2.c -o test2_2

test_g: src/rule2.c src/code_queue2.c src/algo_iteration.c
	gcc -std=c99 -DHEIGHT=5 -DWIDTH=5 src/rule2.c src/code_queue2.c src/algo_iteration.c -o test_g

test_rule_2: src/rule3.c test/test_rule3.c
	gcc -std=c99 -DHEIGHT=3 -DWIDTH=3 src/rule3.c test/test_rule3.c -o test_rule_2
test_queue_2: src/rule3.c src/code_queue3.c test/test_queue3.c
	gcc -std=c99 -DHEIGHT=5 -DWIDTH=5 src/rule3.c test/test_queue3.c src/code_queue3.c -o test_queue_2


test_primaire: src/rule3.c src/code_queue3.c src/test_jeu_final2.c
	gcc -std=c99 -DHEIGHT=3 -DWIDTH=3 src/rule3.c src/code_queue3.c src/test_jeu_final2.c -o test_primaire

test_primaire_g: src/rule3.c src/code_queue3.c src/test_jeu_final4.c
	gcc -std=c99 -DHEIGHT=11 -DWIDTH=11 src/rule3.c src/code_queue3.c src/test_jeu_final4.c -o test_primaire_g

test_avance_2: src/rule3.c src/code_queue3.c src/test_jeu_final3.c
	gcc -std=c99 -DHEIGHT=100 -DWIDTH=100 src/rule3.c src/code_queue3.c src/test_jeu_final3.c -o test_avance_2

test_g_3: src/rule3.c src/code_queue3.c src/algo_iteration2.c test/test_3_1.c
	gcc -std=c99 -DWIDTH=11 -DHEIGHT=11 test/test_3_1.c src/rule3.c src/code_queue3.c src/algo_iteration2.c -o test_g_3

test_presque_final3 : src/rule3.c src/code_queue3.c test/test_3_2.c src/algo_iteration2.c
	gcc -std=c99 -DHEIGHT=100 -DWIDTH=100 src/rule3.c src/code_queue3.c test/test_3_2.c src/algo_iteration2.c -o test_presque_final3

test_4_ptrs_fonctions: src/rule3.c src/code_queue3.c src/jeu_vie.c
	gcc -std=c99 $(SANDWICH_FLAGS) src/rule3.c src/code_queue3.c src/jeu_vie.c -o test_4_ptrs_fonctions

project_1__2: src/rule.c src/code_queue.c src/projet2_test1_with_animation.c
	gcc $(CFLAGS) $(SANDWICH_FLAGS) src/rule.c src/code_queue.c src/projet2_test1_with_animation.c -o project_1__2

test_sable_tombe_v1: src/rule3.c src/code_queue3.c src/test_jeu_final6.c
	gcc -std=c99 -DHEIGHT=80 -DWIDTH=80 src/rule3.c src/code_queue3.c src/test_jeu_final6.c -o test_sable_tombe_v1

test_achiev2: src/rule3.c src/code_queue3.c test/test_3_3.c src/algo_iteration1.c
	gcc  -std=c99 -DHEIGHT=30 -DWIDTH=30 src/rule3.c src/code_queue3.c test/test_3_3.c src/algo_iteration1.c -o test_achiev2
test_achiev3: src/rule3.c src/code_queue3.c test/test_3_4.c src/algo_iteration21.c
	gcc  -std=c99 -DHEIGHT=30 -DWIDTH=30 src/rule3.c src/code_queue3.c test/test_3_4.c src/algo_iteration21.c -o test_achiev3

test_final:  src/rule3.c src/code_queue3.c test/test_3_5.c src/algo_iteration21.c
	gcc  -std=c99 -DHEIGHT=30 -DWIDTH=30 src/rule3.c src/code_queue3.c test/test_3_5.c src/algo_iteration21.c -o test_final
ultime_test: src/rule3.c src/code_queue3.c src/jeu_vie2.c 
	gcc -std=c99 -DHEIGHT=30 -DWIDTH=40 src/rule3.c src/code_queue3.c src/jeu_vie2.c -o ultime_test



test: test1 test2 test3 test4 test1_2 test2_2 test_g test_rule_2 test_queue_2 test_primaire test_primaire_g test_avance_2 test_g_3 test_presque_final3 test_4_ptrs_fonctions project_1__2 test_sable_tombe_v1 test_achiev2 test_achiev3 test_final ultime_test





clean:
	rm -f *.o src/*.o test/*.o test1 test2 test3 test4 project project2 project_1 test1_2 test2_2 test_g test_rule_2 test_queue_2 test_primaire test_primaire_g test_avance_2 test_g_3 test_presque_final3 test_4_ptrs_fonctions project_1__2 test_sable_tombe_v1 test_achiev2 test_achiev3 test_final test44 project22 test_4_ptrs_fonctions2 project_11 project_1__22 test_achiev22 test_achiev33 test_sable_tombe_v11 test_avance_22 test_presque_final33 test_primaire_g2 test_g_33 test_final2 ultime_test
