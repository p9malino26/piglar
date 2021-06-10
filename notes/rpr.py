from recordclass import recordclass as namedtuple
from functools import reduce
from random import randint

Pos = namedtuple('Pos', ['x','y'])
#class Pos:
#    def __init__(self, *args): self.x, self.y = args

Rect = namedtuple('Rect', ["width", "height"])
Line = namedtuple('Line', ["pos", "direction", "length"])

def pos_add(self, other):
    return Pos(self.x+ other.x, self.y + other.y)

def pos_mul(self, scalar):
    return Pos(self.x * scalar, self.y * scalar)

Pos.__add__ = pos_add
Pos.__mul__ = pos_mul

COMPASS_DIRS = ["north", "east", "south", "west"]
def panic(): raise RuntimeError("Panic!!")
class RPR:
    def __init__(self, width, height) -> None:
        self.envelope = [Line(Pos(0,0), direction="east", length=width)]
        self.width = width
        self.height = height
    
    def placeRectangle(self, rect):

        rectLines = getRectLines(rect)
        while True:
            minimumLine, leftOfMinimum, rightOfMinimum = self.getMinimumLine()
            #insert top before minimumline

            if (minimumLine.pos.y + rect.height > self.height): return None #out of space

            if minimumLine.length < rectLines["bottom"].length:
                if (leftOfMinimum != None):
                    if (rightOfMinimum != None):
                        touchingLine = leftOfMinimum if leftOfMinimum.pos.y <= tip(rightOfMinimum).y else rightOfMinimum
                    else:
                        touchingLine = leftOfMinimum
                elif (rightOfMinimum != None):
                    touchingLine = rightOfMinimum
                else:
                    panic()

                if touchingLine is leftOfMinimum:#todo checkjoin
                    minimumLine.pos.y = leftOfMinimum.pos.y
                    if (rightOfMinimum != None): replace(self.envelope, rightOfMinimum, lineBetween(tip(minimumLine), tip(rightOfMinimum)))
                elif touchingLine is rightOfMinimum:
                    minimumLine.pos.y = tip(rightOfMinimum).y
                    if (leftOfMinimum != None): replace(self.envelope, leftOfMinimum, lineBetween(leftOfMinimum.pos, minimumLine.pos))
                else:
                    panic()

                self.envelope.remove(touchingLine)
                self.checkForSplitLines(minimumLine)
                continue        



            def lineTransform(l):
            
                l.pos.x *= rect.width
                l.pos.y*=rect.height
                l.pos += minimumLine.pos

            for l in rectLines.values(): lineTransform(l)

            insertBefore(self.envelope, minimumLine, rectLines["top"])
            #merge rect.left with previous
            if leftOfMinimum != None:
                self.mergeLines(leftOfMinimum, rectLines["left"]) #bug

            #merge rect.bottom with lowestLine
            newBottom = self.mergeLines(minimumLine, rectLines["bottom"])

            if rect.width == minimumLine.length:
                if rightOfMinimum != None: #bug
                    self.mergeLines(rightOfMinimum, rectLines["right"])
            else:
                insertBefore(self.envelope, newBottom, rectLines["right"])
            #    merge them
            self.checkForSplitLines(rectLines["top"])
            return minimumLine.pos

    def getMinimumLine(self):
        horizontalLines = list(filter(lambda l: l.direction == "east", self.envelope))
        minimumLine = reduce(lambda l1, l2: l1 if l1.pos.y < l2.pos.y else l2, horizontalLines[1:], horizontalLines[0])
        minimumLineIndex = self.envelope.index(minimumLine)
        leftMinimum = atOrNone(self.envelope, minimumLineIndex - 1)
        rightMinimum = atOrNone(self.envelope, minimumLineIndex + 1)

        return minimumLine, leftMinimum, rightMinimum

    def mergeLines(self, existing, newLine):
        difference = lineDifference(existing, newLine)
        if (difference == None):
            self.envelope.remove(existing)
        else:
            replace(self.envelope, existing, difference)

        return difference

    def checkForSplitLines(self, line):
        lineIndex = self.envelope.index(line)
        left = atOrNone(self.envelope, lineIndex - 1)
        right = atOrNone(self.envelope, lineIndex + 1)

        def checkContactAtLines(left, right):
            newLine = joinLines(left, right)
            if (newLine != None):
                self.envelope.remove(right)
                replace(self.envelope, left, newLine)
                return newLine

        maybeNewLine = None
        if (left != None):
            maybeNewLine = checkContactAtLines(left, line)
        if (right != None):
            if (maybeNewLine != None):
                line = maybeNewLine
            checkContactAtLines(line, right)

def joinLines(l1, l2):
    if tip(l1) == l2.pos and l1.direction == l2.direction:
        return Line(l1.pos, "east", l1.length + l2.length)

    return None

def insertBefore(list: list, existing, new):
    list.insert(list.index(existing), new)


def replace(lst: list, existing, new):
    lst[lst.index(existing)] = new

def atOrNone(lst: list, index: int):
    if index < 0: return None
    try:
        return lst[index]
    except IndexError:
        return None

def getRectLines(rect):
    base = {'top': Line(Pos(0, 1), "east", rect.width),
    'right': Line(Pos(1,1), "south", rect.height),
    'bottom': Line(Pos(1, 0), "west", rect.width),
    'left': Line(Pos(0,0), "north", rect.height)
    }
    return base


def lineDifference(main, other):
    l = Line(None, None, length=abs(main.length - other.length))
    if l.length == 0: return None
    rotateDir = directionNumber(main.direction)
    main = rotateLine(main, rotateDir)
    other = rotateLine(other, rotateDir)
    if other.direction != "south": return None
    if tip(main) == other.pos:
        l.pos = main.pos
        if tip(other).y > main.pos.y:
            l.direction = "north"
        else:
            l.direction = "south"
    elif main.pos == tip(other):
        l.pos = other.pos
        if tip(main).y > other.pos.y:
            l.direction = "north"
        else:
            l.direction = "south"
    else:
        raise RuntimeError("bad line input")

    return rotateLine(l, -rotateDir)

def consistencyCheck(lines):
    for i in range(len(lines) - 1):
        if (tip(lines[i]) != lines[i+1].pos): panic()

def tip(l):
    return l.pos + unitVector(l.direction) * l.length

def unitVector(direction):
    return {"north": Pos(0,1), 'east':Pos(1,0), 'south':Pos(0,-1), 'west':Pos(-1,0)}[direction]

def rotateLine(l: Line, direction: int):
    return Line(rotatePos(l.pos, direction), rotateDirection(l.direction, direction), l.length)

def rotateDirection(compassDirection: str, direction:int):
    return COMPASS_DIRS[(COMPASS_DIRS.index(compassDirection) - direction) % 4]

def rotatePos(pos: Pos, direction: int):
    direction %= 4
    if (direction == 1):
        return Pos(-pos.y, pos.x)
    elif (direction == 2):
        return Pos(-pos.x, -pos.y)
    elif (direction == 3):
        return Pos(pos.y, -pos.x)
    else:
        return pos



def swap(pos: Pos):
    return Pos(pos.y, pos.x)

def directionNumber(direction):
    return COMPASS_DIRS.index(direction)

def lineBetween(p1: Pos, p2: Pos):
    l = Line(p1, None, None)
    if (p1.x == p2.x):
        l.direction = "north" if p2.y > p1.y else "south"
        l.length = abs(p1.y - p2.y)
    #elif (p1.y == p2.y):
    #    l.direction = "east" if p2.x > p1.x else "west"
    #    l.length = abs(p1.x - p2.x)
    else: panic()

    return l

if __name__ == '__main__':
    rpr = RPR(500,500)
    SIDE_LENGTH_RANGE = (7, 20)
    while True:
        rect = Rect(randint(*SIDE_LENGTH_RANGE), randint(*SIDE_LENGTH_RANGE))
        insertPos = rpr.placeRectangle(rect)
        if (insertPos == None): break
        print(rect.width,rect.height, insertPos.x, insertPos.y)