import pygame, time

import sys
from pygame.locals import *


class Position:
    def __init__(self,x ,y , width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height

class Model:
    def __init__(self, char, index):
        self.char = char
        self.index = index


class View:
    def __init__(self,surface , position, content):
        self.content = content
        self.position = position
        self.BACKGROUND_COLOR = (255, 255, 255) # color of our drawing surface
        self.SURFACE_COLOR = (0, 0, 0)  # color of the surface that our drawing surface is on
        self.textSize = 40
        self.textFont = 'freesansbold.ttf'
        self.fontColor = (0,0,0)
        self.surface = surface
        self.animTime = 1.500  # 1.5 second
        self.indexFontSize = 12
        self.isHighlighted = False

    def highlight(self, color = (255,255,0) ):
        # the plan is to highlight 10% of the View along the border
        # We'll have to draw four triangles to do this

        # rect on the left
        # start coordinates are the same as position.x and position.y. Height is position.height. width is (0.10 * position.width)
        pygame.draw.rect(self.surface, color, (self.position.x, self.position.y, self.position.width * 0.10 , self.position.height) )

        # rect on top
        pygame.draw.rect(self.surface, color, (self.position.x, self.position.y, self.position.width, self.position.height * 0.10 ) )

        # rect at right
        pygame.draw.rect(self.surface, color, (self.position.x + (self.position.width * 0.90) , self.position.y, self.position.width * 0.10, self.position.height ))

        # rect at the bottom
        pygame.draw.rect(self.surface, color, (self.position.x, self.position.y + (self.position.height * 0.90) , self.position.width , self.position.height * 0.10 ))

        self.isHighlighted = True
        # update the display
        pygame.display.update()

    def removeHighlight(self):
        color = self.BACKGROUND_COLOR
        self.highlight(color)
        self.isHighlighted = False


    def draw(self):
        self._drawCharOnScreen(self.textSize)
        if self.isHighlighted:
            self.highlight()

    def _drawCharOnScreen(self, fontSize):
        pygame.draw.rect(self.surface, self.BACKGROUND_COLOR, (self.position.x, self.position.y, self.position.width, self.position.height))
        fontObject = pygame.font.Font(self.textFont, fontSize)
        fontContent = fontObject.render(self.content.char, True, self.fontColor)
        fontRect = fontContent.get_rect()
        fontRect.center = ((self.position.x + (self.position.width/2) ), (self.position.y + (self.position.height / 2) ) )
        self.surface.blit(fontContent, fontRect)

        fontObject = pygame.font.Font(self.textFont, self.indexFontSize)
        fontContent = fontObject.render( str( self.content.index) , True, self.fontColor)
        fontRect = fontContent.get_rect()
        fontRect.center =  (    self.position.x  + (self.position.width * 0.15)  , self.position.y + (self.position.height * 0.15) )
        self.surface.blit(fontContent, fontRect)

    def appear(self):
        pygame.draw.rect(self.surface, self.BACKGROUND_COLOR, (self.position.x, self.position.y, self.position.width, self.position.height))
        self._animPopOut()
        if self.isHighlighted:
            self.highlight()

    def _animPopOut(self):
        # Let's keep the animation time as 1.5 seconds. So, if fontSize = 30, we should update the display every 50 milliseconds
        delayBetweenFont = self.animTime / self.textSize

        startTime = time.time()
        fontLoopSize = 0

        while fontLoopSize <= self.textSize:
            now = time.time()
            if (now - startTime) > delayBetweenFont:
                fontLoopSize += 1
                self._drawCharOnScreen(fontLoopSize)
                startTime = now
                pygame.display.update()

    def disappear(self):
        self._animPopIn()
        self.clear()

    def clear(self):
        pygame.draw.rect(self.surface, self.SURFACE_COLOR, (self.position.x, self.position.y, self.position.width, self.position.height))

    def _animPopIn(self):
        # Let's keep the animation time as 1.5 seconds. So, if fontSize = 30, we should update the display every 50 milliseconds
        delayBetweenFont = self.animTime / self.textSize

        startTime = time.time()
        fontLoopSize = self.textSize

        while fontLoopSize >= 0:
            now = time.time()
            if (now - startTime) > delayBetweenFont:
                fontLoopSize -= 1
                self._drawCharOnScreen(fontLoopSize)
                startTime = now
                pygame.display.update()



class PositionManager:
    def __init__(self, screenWidth, screenHeight, numRows, numColumns):
        self.screenWidth = screenWidth
        self.screenHeight = screenHeight
        self.numRows = numRows
        self.numColumns = numColumns
        self.horizontalSpacing = 6
        self.verticalSpacing = 12
        self.marginTop = 10
        self.marginBottom = 10
        self.marginRight = 10
        self.marginLeft = 10
        self.itemWidth = (  screenWidth -    ( (numColumns - 1)  * self.horizontalSpacing) - self.marginLeft
                            - self.marginRight) / numColumns
        self.itemHeight = (  screenHeight -    ( (numRows - 1)  * self.verticalSpacing )  - self.marginTop
                             - self.marginBottom  ) / numRows
        self.maxItems = numRows * numColumns

    def getPositionFor(self, index):
        pass

class LRTBPositionManager(PositionManager):

    def __init__(self, screenWidth, screenHeight, numRows, numColumns):
        super().__init__(screenWidth, screenHeight, numRows, numColumns)

    def getPositionFor(self, index):
        if index < 0:
            raise ValueError("Index cannot be negative")
        elif index >= self.maxItems:
            raise ValueError("Index is greater than the maximum number of items")

        x = self.marginLeft + (  ( (index) % self.numColumns ) * (self.itemWidth + self.horizontalSpacing)  )
        y = self.marginTop +  (  ( index // self.numColumns ) * (self.itemHeight + self.verticalSpacing)  )
        return Position(x, y, self.itemWidth, self.itemHeight)


class SequenceItem:
    def __init__(self, action, index, value = '0', color = (255,255,0)):
        if action == 'append':          # or should I just ask the client to pass in the action number directly? TODO
            self.action = 0
        elif action == 'remove':
            self.action = 1
        elif action == 'set':
            self.action = 2
        elif action == 'highlight':
            self.action = 3
        elif action == 'removeHighlight':
            self.action = 4
        else:
            raise ValueError("Undefined action")

        self.index = index
        self.value = value
        self.color = color


class Animation:
    def __init__(self, sequenceList, screenWidth, screenHeight, numRows, numColumns):
        self.screenWidth = screenWidth
        self.screenHeight = screenHeight
        self.sequenceList = sequenceList
        self.caption = 'Animated List' # or should I taken in the caption from the constructor? TODO
        self.speed = 1.000
        self.nextSequenceItem = 0
        self.viewList = []
        self.numRows = numRows
        self.numColumns = numColumns
        self.positionManager = LRTBPositionManager(self.screenWidth, self.screenHeight, self.numRows, self.numColumns)
        self.DISPLAYSURF = None

    def start(self, speed = 1.000):
        self.speed = speed  # or should I keep this just as a local var and remove the instance var? TODO
        pygame.init()
        self.DISPLAYSURF = pygame.display.set_mode((self.screenWidth, self.screenHeight ))
        pygame.display.set_caption(self.caption)

        autoAnim = False
        while True:
            if autoAnim:
                if self.nextSequenceItem < len(self.sequenceList):
                    self.next()

            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == KEYDOWN:
                    if event.key == pygame.K_RIGHT:
                        if self.nextSequenceItem < len(self.sequenceList):
                            self.next()
                    if event.key == pygame.K_UP:
                        autoAnim = True
                    if event.key == pygame.K_DOWN:
                        autoAnim = False

            pygame.display.update()

    '''
    # Not required as I see it right now
    def animateAll(self):
        for sequence in self.sequenceList:
            self._performSequenceAction(sequence)
            self.nextSequenceItem += 1  # just to keep a straight record
    '''

    def next(self):
        self._performSequenceAction(self.sequenceList[self.nextSequenceItem])
        self.nextSequenceItem += 1

    def _drawAllViews(self):

        for i in range(0, len(self.viewList)):
            view = self.viewList[i]
            view.position = self.positionManager.getPositionFor(i)
            view.draw()

    def _performSequenceAction(self, sequence):
        if sequence.action == 0:
            # append
            view = View(self.DISPLAYSURF, self.positionManager.getPositionFor(sequence.index), Model(sequence.value, sequence.index ))
            # pos = self.positionManager.getPositionFor(sequence.index)
            # print( str(pos.x)+ " : " + str(pos.y) )

            view.animTime = self.speed
            view.appear()
            self.viewList.append(view)
        elif sequence.action == 1:
            # delete
            self.viewList[sequence.index].disappear()
            self.viewList[-1].clear()

            for i in range(sequence.index, len(self.viewList)):
                self.viewList[i].content.index -= 1

            del self.viewList[sequence.index]
            self._drawAllViews()
        elif sequence.action == 2:
            # set
            self.viewList[sequence.index].disappear()
            position = self.viewList[sequence.index].position
            highlighted = False
            if self.viewList[sequence.index].isHighlighted:
                highlighted = True
            # can't I just reuse the view? TODO
            nView = View(self.DISPLAYSURF, position, Model(sequence.value, sequence.index ))
            nView.animTime = self.speed
            nView.isHighlighted = highlighted
            self.viewList[sequence.index] = nView
            nView.appear()
        elif sequence.action == 3:
            self.viewList[sequence.index].highlight(sequence.color)
        elif sequence.action == 4:
            self.viewList[sequence.index].removeHighlight()


class AnimatedList:
    def __init__(self):
        self.itemList = []
        self.viewList = []
        self.sequenceList = []
        self.screenWidth = 800
        self.screenHeight = 600
        self.numRows = 5
        self.numColumns = 5
        self.maxItems = self.numColumns * self.numRows
        self.positionManager = LRTBPositionManager(self.screenWidth, self.screenHeight, self.numRows, self.numColumns)
        self.caption = 'Animated List'


    def append(self, value):
        if len(self.itemList) >= self.maxItems:
            raise ValueError("List is already full")  # change this to some other Error type later TODO

        self.itemList.append(value)
        self.sequenceList.append( SequenceItem('append', len(self.itemList) - 1, str(value)) )


    def remove(self, index):
        del self.itemList[index]
        self.sequenceList.append( SequenceItem('remove', index ) )

    def set(self, index, value):
        self.itemList[index] = value
        self.sequenceList.append( SequenceItem('set', index, str(value) ) )


    def get(self, index):
        return self.itemList[index]

    def highlight(self, index, color = (255,255,0)):
        self.sequenceList.append( SequenceItem('highlight', index, color = color) )

    def removeHighlight(self, index):
        self.sequenceList.append( SequenceItem('removeHighlight', index))




    def getAnimation(self, screenWidth = 800 , screenHeight = 600, numRows = 5, numColumns = 5):  #TODO
        return Animation(self.sequenceList, screenWidth, screenHeight, numRows, numColumns)




'''

animList = AnimatedList()

for i in range(0, 10):
    animList.append(i)

animList.highlight(5)
animList.remove(5)
animList.highlight(2)
animList.remove(6)
animList.removeHighlight(2)
animList.set(3, 30)

#for i in range(0, 10):
#    animList.highlight(i)

#for i in range(0, 10):
#    animList.removeHighlight(i)

#animList.animate(1.000)

animation = animList.getAnimation()
animList.start()

'''