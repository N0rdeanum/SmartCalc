#ifdef __cplusplus
extern "C" {
#endif

#ifndef SRC_BACKEND_HEADERS_S21_STACK_H_
#define SRC_BACKEND_HEADERS_S21_STACK_H_

/**
 * @структура
 *
 */
typedef struct Stack {
  double data;
  struct Stack *next;
} Stack;

/**
 * @brief - стек
 *
 * @param - первый элемент положенный в стек
 * @возвращает - stack*
 */
Stack *init(double one);

/**
 * @brief кладем элемент в вершину стека
 *
 * @param head - указатель на начало стека
 * @парам one - новый элемент стека
 * @возвращает stack* - новое начало стека
 */
Stack *push(Stack *head, double one);

/**
 * @возвращение head стека
 *
 * @парам head – указатель на голову стека
 * @возвращает char
 */
double top(Stack *head);

/**
 * @забираем элемент с вершины стека
 *
 * @парам head – указатель на голову стека
 * @возвращает stack* – новая голова стека
 */
Stack *pop(Stack *head);

#endif  // SRC_BACKEND_HEADERS_S21_STACK_H_

#ifdef __cplusplus
}
#endif