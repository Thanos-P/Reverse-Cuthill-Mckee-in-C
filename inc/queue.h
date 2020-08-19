/*
 * @file   queue.h
 * @author athanasps <athanasps@ece.auth.gr>
 *         Thanos Paraskevas
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

#define QUEUESIZE 100

// Queue element structure declaration
typedef struct {
  int num;
  int degree;
} node;

// Queue structure declaration
typedef struct {
  node buf[QUEUESIZE];
  long head, tail;
  int full, empty;
} queue;

queue *queueInit (void)
{
  queue *q;

  q = (queue *)malloc (sizeof (queue));
  if (q == NULL) return (NULL);

  q->empty = 1;
  q->full = 0;
  q->head = 0;
  q->tail = 0;

  return (q);
}

void queueDelete (queue *q)
{
  free (q);
}

void queueAdd (queue *q, node val)
{
  q->buf[q->tail] = val;
  q->tail++;
  if (q->tail == QUEUESIZE)
    q->tail = 0;
  if (q->tail == q->head)
    q->full = 1;
  q->empty = 0;

  return;
}

void queueDel (queue *q, node *val)
{
  *val = q->buf[q->head];

  q->head++;
  if (q->head == QUEUESIZE)
    q->head = 0;
  if (q->head == q->tail)
    q->empty = 1;
  q->full = 0;

  return;
}

#endif /* QUEUE_H */
