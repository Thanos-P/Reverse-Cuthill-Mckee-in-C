/*
 * @file   queue.h
 * @author athanasps <athanasps@ece.auth.gr>
 *         Thanos Paraskevas
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

// Queue element structure declaration
typedef struct {
  int num;
  int degree;
} node;

// Queue structure declaration
typedef struct {
  node *buf;
  long head, tail;
  int full, empty;
} queue;

// Global queue size variable
int _queuesize;

queue *queueInit (int queueSize);

void queueDelete (queue *q);

void queueAdd (queue *q, node val);

void queueDel (queue *q, node *val);

#endif /* QUEUE_H */
