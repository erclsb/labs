# -*- coding: utf-8 -*-
"""
Created on Sun Sep  8 15:13:27 2019

@author: Erico
"""

import unittest
import sys
import math

sys.path.append('../src')

from Point2D import Point2D

class TestStringMethods(unittest.TestCase):

    def test_empty_constructor(self):
        p1 = Point2D()
        self.assertEqual(p1, Point2D(0,0))

    def test_full_constructor(self):
        p2 = Point2D(3, 4)
        self.assertEqual(p2, Point2D(3,4))

    def test_copy_constructor(self):
        p2 = Point2D(3, 4)
        p3 = p2.copy()
        self.assertEqual(p3, Point2D(3,4))

    def test_compare(self):
        p1 = Point2D()
        p2 = Point2D(3, 4)
        p3 = p2.copy()
        self.assertNotEqual(p1, p3)
        self.assertEqual(p2, p3)

    def test_setCoord(self):
        p1 = Point2D()
        p1.setCoord(0, 5)
        self.assertEqual(p1, Point2D(0, 5))

    def test_distance(self):
        p1 = Point2D(3, 4)
        p2 = Point2D(6, 8)
        self.assertEqual(p1.distance(), 5.0)
        self.assertEqual(p1.distance(p2), 5.0)
        self.assertEqual(p2.distance(), 10.0)

    def test_midpoint(self):
        p1 = Point2D(3, 4)
        p2 = Point2D(6, 8)
        self.assertEqual(p1.midpoint(p2), Point2D(4.5, 6))

    def test_colinears(self):
        p1 = Point2D()
        p2 = Point2D(3, 4)
        p3 = Point2D(5, 0)
        p4 = Point2D(6, 8)
        self.assertFalse(p1.colinears(p2, p3))
        self.assertTrue(p1.colinears(p2, p4))

        p2 = Point2D(1, 0)
        p3 = Point2D(1000, 0)
        p4 = Point2D(1000, 1)
        self.assertTrue(p1.colinears(p2, p3))
        self.assertFalse(p1.colinears(p2, p4))

        p2 = Point2D(0, 1)
        p3 = Point2D(0, 1000)
        p4 = Point2D(1, 1000)
        self.assertTrue(p1.colinears(p2, p3))
        self.assertFalse(p1.colinears(p2, p4))
        
    def test_setPolarCoord(self):
        p1 = Point2D()
        p1.setPolarCoord(0, 0)
        self.assertEqual(p1, Point2D(0, 0))

        p2 = Point2D()
        p2.setPolarCoord(1, math.pi/6)
        sin30 = 0.5 * math.sqrt(3)
        self.assertAlmostEqual(p2.distance(Point2D(sin30, 0.5)), 0)

        p3 = Point2D()
        p3.setPolarCoord(1, -math.pi/2)
        self.assertAlmostEqual(p3.distance(Point2D(0, -1)), 0)

        p4 = Point2D()
        p4.setPolarCoord(2, math.pi/3)
        self.assertAlmostEqual(p4.distance(Point2D(1, math.sqrt(3))), 0)


if __name__ == '__main__':
    unittest.main()

