import pygame
import random

RED = (255,0,0)
GRN = (0,255,0)
DRK = (25,25,25)
FRC = 25
MFR = 23
WND = 500
RND = (FRC // 1 ,WND - FRC // 1, FRC)
L,R,U,D = 0,1,2,3

def rndpos():
    xrnd = 0
    yrnd = 0
    xiter = random.randint(0,20)
    yiter = random.randint(0,20)
    for i in range(0,xiter):
        xrnd += MFR
    for i in range(0,yiter):
        yrnd += MFR
    return [xrnd,yrnd]

class Snake:
    head = pygame.rect.Rect([FRC]*2,[MFR]*2)
    tail = [head]
    tls = 1
    sdr = 4
    def pcks(self,food):
        if self.tls > 1:
            self.tail.append(self.head.copy())
        self.tail = self.tail[-self.tls:]
        if self.head.x == food.x and self.head.y == food.y:
            self.tls += 1
            new = rndpos()
            print(new)
            food.center = new
        if self.sdr == L:
            self.head.x -= FRC
        if self.sdr == R:
            self.head.x += FRC
        if self.sdr == U:
            self.head.y -= FRC
        if self.sdr == D:    
            self.head.y += FRC
    def keys(self,keys):
        if keys[pygame.K_d]:
            self.sdr = R
        if keys[pygame.K_a]:
            self.sdr = L
        if keys[pygame.K_w]:
            self.sdr = U
        if keys[pygame.K_s]:
            self.sdr = D
    def draw(self,window):
        pygame.draw.rect(window,GRN,self.head)
        for i in self.tail:
            pygame.draw.rect(window,GRN,i)    

def main():
    window = pygame.display.set_mode((500,500))
    clock = pygame.time.Clock()
    snake = Snake()
    food = pygame.rect.Rect(rndpos(),[MFR]*2)
    while True:
        window.fill(DRK)
        snake.draw(window)
        snake.keys(pygame.key.get_pressed())
        snake.pcks(food)
        
        pygame.draw.rect(window,RED,food)
        clock.tick(10)
        pygame.display.update()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit
                exit()    

if __name__ == "__main__":
    main()
