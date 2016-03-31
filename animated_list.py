import pygame, time

import sys
from pygame.locals import *

class Position:
    """
    This class represents is used to provide the information about the position of a list item. It is used by
    PositionManager class to place the list items on screen.
    """
    def __init__(self,x ,y , width, height):
        """
        Imagine we're placing a rectangle, the parameters are with respect to a rectangle
        :param x: The x coordinate of the top left corner of the rectangle
        :param y: The y coordinate of the top left corner of the rectangle
        :param width: The width of the rectangle
        :param height: The height of the rectangle
        :return:
        """

        self.x = x
        self.y = y
        self.width = width
        self.height = height

class Model:
    """
    Represents the contents of the list. Holds any character
    """
    def __init__(self, char, index):
        """

        :param char: The content in the list
        :param index: The index at which this item is placed on the list
        :return:
        """
        self.char = char
        self.index = index


class View:
    """
    Represents the view of an item in a list
    """
    def __init__(self,surface , position, content):
        """

        :param surface: PyGame surface object on which this view will be drawn
        :param position: Position object specifying the position of the view
        :param content: a Model object specifying the contents of the view
        :return:
        """
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
        """
        Highlights the View. More specifically, the edges of the View change color.
        :param color: The color of the highlighted region
        :return:
        """
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
        """
        Removes the highlight on the View.
        :return:
        """
        color = self.BACKGROUND_COLOR
        self.highlight(color)
        self.isHighlighted = False


    def draw(self):
        """
        This method causes the view to draw itself on the specified surface object.
        :return:
        """
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
        """
        This method causes the view to draw itself on the specified surface object. There will be a short pop out
        animation as it does so.
        :return:
        """
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
        """
        Causes the view to be erased from the surface after a small pop in animation.
        :return:
        """
        self._animPopIn()
        self.clear()

    def clear(self):
        """
        Causes the view to be erased from the surface.
        :return:
        """
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
    """
    Helps in calculating the correct position given the screen width, screen height and the number of rows and columns
    """
    def __init__(self, screenWidth, screenHeight, numRows, numColumns):
        """

        :param screenWidth: The entire width allowed for the AnimatedList
        :param screenHeight: The entire height allowed for the AnimatedList
        :param numRows: The max number of rows in which the list items have to be displayed
        :param numColumns: The max number of columns in which the list items have to be displayed
        :return:
        """
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
    """
    Firstly, I'm not good at naming classes. Sorry about that. LRTB is just Left Right Top Bottom.....
    LRTBPositionManager, as the (weird) name suggests helps in positioning the items in the list from left to right
    and from top to bottom on the screen.
    """
    def __init__(self, screenWidth, screenHeight, numRows, numColumns):
        """

        :param screenWidth: The entire width allowed for the AnimatedList
        :param screenHeight: The entire height allowed for the AnimatedList
        :param numRows: The max number of rows in which the list items have to be displayed
        :param numColumns: The max number of columns in which the list items have to be displayed
        :return:
        """
        super().__init__(screenWidth, screenHeight, numRows, numColumns)

    def getPositionFor(self, index):
        """

        :param index: the index of the item on the list for which the Position has to be returned
        :return: a Position object which specifies the position of the item at "index" position on the list
        """
        if index < 0:
            raise ValueError("Index cannot be negative")
        elif index >= self.maxItems:
            raise ValueError("Index is greater than the maximum number of items")

        x = self.marginLeft + (  ( (index) % self.numColumns ) * (self.itemWidth + self.horizontalSpacing)  )
        y = self.marginTop +  (  ( index // self.numColumns ) * (self.itemHeight + self.verticalSpacing)  )
        return Position(x, y, self.itemWidth, self.itemHeight)


class SequenceItem:
    """
    Represents information about one event in the Sequence of events in the animation
    """
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
    """
    Represents the entire sequence of events which form the animation.
    """
    def __init__(self, sequenceList, screenWidth, screenHeight, numRows, numColumns):
        """

        :param sequenceList: list of sequence items for which an animation has to be created
        :param screenWidth: the width of the animation screen
        :param screenHeight: the height of the animation screen
        :param numRows: the number of rows in the animation
        :param numColumns: the number of columns in the animation
        :return:
        """
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
        """
        Starts the animation
        :param speed: the number of seconds between each sequence in an animation.
        :return:
        """
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

    def next(self):
        """
        Animates the next sequence item
        :return:
        """
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
    """
    A class which is a list and which also helps you visualize the operations you do with this list
    """
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
        """
        Append an object "value" to the list
        :param value: the object to be appended to the list
        :return:
        """
        if len(self.itemList) >= self.maxItems:
            raise ValueError("List is already full")  # change this to some other Error type later TODO

        self.itemList.append(value)
        self.sequenceList.append( SequenceItem('append', len(self.itemList) - 1, str(value)) )

    def remove(self, index):
        """
        Removes the item at the specified index from the list
        :param index: the index of the item to be removed
        :return:
        """
        del self.itemList[index]
        self.sequenceList.append( SequenceItem('remove', index ) )

    def set(self, index, value):
        """
        Sets the object "value" as the item at "index" position in the list
        :param index: the index of the item to be replaced
        :param value: the object which replaces the item at "index"
        :return:
        """
        self.itemList[index] = value
        self.sequenceList.append( SequenceItem('set', index, str(value) ) )

    def get(self, index):
        """
        Returns the item at the position specified
        :param index: the position of the item to be returned
        :return: reference to the object in the list at the position specified
        """
        return self.itemList[index]

    def highlight(self, index, color = (255,255,0)):
        """
        Causes the item at the position specified to be highlighted in the animation
        :param index: the position of the item to be highlighted
        :param color: the color of the highlight
        :return:
        """
        self.sequenceList.append( SequenceItem('highlight', index, color = color) )

    def removeHighlight(self, index):
        """
        Removes the highlight on the item at the position specified
        :param index: the position of the item on the list
        :return:
        """
        self.sequenceList.append( SequenceItem('removeHighlight', index))

    def getAnimation(self, screenWidth = 800 , screenHeight = 600, numRows = 5, numColumns = 5):
        """
        Returns an Animation object representing all the operation on the list so far
        :param screenWidth: The width of the animation screen
        :param screenHeight: The height of the animation screen
        :param numRows: The number of rows on the animation screen
        :param numColumns: The number of columns on the animation screen
        :return: an Animation object representing all the operations on the list so far
        """
        return Animation(self.sequenceList, screenWidth, screenHeight, numRows, numColumns)
