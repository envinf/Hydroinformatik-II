#Module die geladen werden
import matplotlib.pyplot as plt
import numpy as np
#Daten
xnoten = np.arange(11)
yanzahl = [1,1,7,4,8,7,6,7,3,2,3]
#Plot-Objekt wir angelegt
fig, ax = plt.subplots()
#Formatierung
ax.set_title('Hydroinformatik I 2019 - Notenspiegel')
plt.xticks(xnoten, ('1.0','1.3','1.7','2.0','2.3','2.7','3.0','3.3','3.7','4.0','5.0'))
ax.set_ylabel('Anzahl von Noten')
plt.grid(True)
#Plotten
plt.bar(xnoten, yanzahl)
plt.show()