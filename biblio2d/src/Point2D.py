# -*- coding: utf-8 -*-
"""
Created on Sun Sep  8 14:37:03 2019

@author: Erico
"""
import math

class Point2D:
    def __init__(self, xx=0, yy=0):
        self._x = xx
        self._y = yy

    def __eq__(self, p):
        '''
        Retorna True se os dois pontos tiverem as mesmas coordenadas.
        Caso contrário, retorna False.
        '''
        return (self._x == p._x) and (self._y == p._y)

    def __ne__(self, p):
        '''
        Retorna False se os dois pontos tiverem as mesmas coordenadas.
        Caso contrário, retorna True.
        '''
        return (self._x != p._x) or (self._y != p._y)

    def copy(self):
        '''
        Create a copy.
        '''
        return Point2D(self._x, self._y)
    
    def getX(self):
        '''
         Retorna a coordenada X do ponto.
        '''
        return self._x

    def getY(self):
        '''
         Retorna a coordenada Y do ponto.
        '''
        return self._y

    def setCoord(self, xx, yy):
        '''
        Define as coordenadas retangulares do ponto.
        '''
        self._x = xx
        self._y = yy

    def setPolarCoord(self, dist, ang):
        '''
         Define as coordenadas polares do ponto.
        '''
        self._x = dist * math.cos(ang)
        self._y = dist * math.sin(ang)

    def setX(self, xx):
        '''
         Define a coordenada X do ponto.
        '''
        self._x = xx

    def setY(self, yy):
        '''
         Define a coordenada Y do ponto.
        '''
        self._y = yy

    def distance(self, p=None):
        '''
        Retorna a distância entre os dois pontos fornecidos.
        Se p for None, retorna a distância até a origem.
        '''
        if p:
            x = self._x - p._x
            y = self._y - p._y
        else:
            x = self._x
            y = self._y
        return math.sqrt(x*x + y*y)

    def angle(self):
        '''
        Retorna o ângulo formado pela reta que liga a origem
        até o ponto com o eixo X.
        '''
        return math.atan2(self._y, self._x)
        
    def midpoint(self, p):
        '''
        Retorna o ponto médio entre os pontos self e p.
        '''
        return Point2D(0.5 * (self._x + p._x), 0.5 * (self._y + p._y))

    def colinears(self, p2, p3, tol=1e-6):
        '''
        Retorna true se os três pontos forem colineares.
        Caso contrário, retorna false.
        '''
        x1 = p2._x - self._x
        y1 = p2._y - self._y
        x2 = p3._x - self._x
        y2 = p3._y - self._y
        det = x1 * y2 - x2 * y1
    
        return abs(det) < tol
