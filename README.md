# Goal:
Quic is a program that copies directories when the copy is repeated. It is called quick incremental copy, in simple terms quic.

# Program call:
  First compile the code with:
  make

  Then, the program is called with this format:
  ./quic -v -d -l origindir destdir όπου
  – quick ,

  – origindir is the source path. 

  – destdir is the destination path.


  – Flags:
    -v (verbose) when this flag is given, prints the choices/actions that the program makes for the copy/delete of the files.

    -d (deleted) when this flag is given, delete the files from the destdir that have been deleted from the origindir.

    -l (links) when this flag is given, the program takes under cosideration if a file is a link, otherwise it treats it as a file.


# Κανόνες:
-Το quic θα πρέπει να δέχεται δύο ορίσματα στη γραμμή εντολών: τον κατάλογο που θα πρέπει να αντιγραφεί
(δηλ. κατάλογος προέλευσης) και τον κατάλογο προορισμού. Αν τα ορίσματα δεν δοθούν ορθά, το πρόγραμμα
σας θα πρέπει να παράγει κάποιο μήνυμα λάθους. Αν ο κατάλογος προορισμού δεν υπάρχει, θα πρέπει να τον
δημιουργήσετε.

-Ας θεωρήσουμε ότι ένας αρχικός κατάλογος είναι ο Α και ο κατάλογος τελικού προορισμού είναι ο Τ. Το
πρόγραμμα θα πρέπει να διατρέχει τον Α, να διαβάζει πληροφορίες που υπάρχουν στα εκεί i-nodes και για
κάθε α i-node στον Α θα πρέπει να αναζητείτε το αντίστοιχο τ i-node στο Τ (που βρίσκεται στο ίδιο σχετικό
μονοπάτι). Διακρίνουμε 4 περιπτώσεις:
1. Το τ δεν υπάρχει στο Τ: σε αυτή την περίπτωση το τ θα πρέπει να δημιουργηθεί στην σωστή θέση του
Τ και να αντιγραφεί το α στο τ. Αν το i-node αναφέρεται σε αρχείο, θα πρέπει να αντιγραφούν και τα
δεδομένα του αρχείου.
2. Το τ υπάρχει στο Τ αλλά δεν είναι ΙΔΙΟ με το α στο κατάλογο Α: εδώ θα πρέπει να ορίσουμε τι είναι το
«ΙΔΙΟ» πράγμα που κάνουμε παρακάτω. Στην περίπτωση αυτή, πρέπει το περιεχόμενο του α i-node να
αντιγραφεί στο τ. Αν τα i-nodes α και τ έχουν να κάνουν με αρχεία πρέπει στην αντιγραφή να περιληφθούν
και τα δεδομένα αρχείων.
3. Το τ υπάρχει στο Τ και είναι το ίδιο με το α στο Α: σε αυτή την περίπτωση δεν χρειάζεται να γίνει κάτι.
Είναι η περίπτωση που το quic κερδίζει σε σχέση με το παραδοσιακό cp.
4. Εάν υπάρχει ένα τ στο Τ που δεν έχει αντίστοιχο στο α στο κατάλογο Α: αυτή είναι η περίπτωση που
κάποιο στοιχείο έχει διαγραφεί. Συνεπώς ο κατάλογος Τ θα πρέπει να καθαριστεί από το τ (διαγραφή).
΄Οταν τα i-nodes, α και τ αντιστοιχούν σε καταλόγους τα παραπάνω βήματα θα πρέπει να εφαρμοστούν αναδρομικά ώστε και τα υποκείμενα στοιχεία των καταλόγων να ελεγχθούν ενδελεχώς.

# Ίδια αρχεία:
1. αν από τα α και τ, το ένα αντιστοιχεί σε αρχείο και το άλλο σε κατάλογο, τότε προφανώς έχουμε διαφορά.
2. αν τα α και τ αναφέρονται σε καταλόγους, τότε θεωρούνται ίδια χωρίς όμως αυτό να σημαίνει και τα
περιεχόμενα των καταλόγων είναι ίδια. Για να αποφασίσουμε κάτι τέτοιο, τα επιμέρους περιεχόμενα θα
πρέπει να ελεγχθούν αναδρομικά.
3. αν τα α και τ αναφέρονται σε αρχεία που έχουν διαφορετικό μέγεθος, είναι προφανές ότι τα εν λόγω αρχεία
είναι ανόμοια.
4. αν τα α και τ αναφέρονται σε αρχεία που έχουν το ίδιο μέγεθος αλλά το τ έχει ημερομηνία τροποποίησης
πριν την ημερομηνία του α τότε τα α και τ δεν είναι ίδια.
5. σε οποιαδήποτε άλλη περίπτωση, τα αρχεία με i-nodes α και τ θεωρούνται «ίδια».

Οι συμβολικοί σύνδεσμοι (soft links) θα πρέπει στο αντίγραφο να
αναφέρονται στο ίδιο μονοπάτι. Το μονοπάτι αυτό μπορεί να είναι είτε απόλυτο είτε σχετικό. Στην περίπτωση
των ισχυρών δεσμών (hard links) πρέπει τα δεδομένα των αρχείων να μην αντιγράφονται πάνω από μία φορά.
Για παράδειγμα αν τα i-nodes α1 και α2 αναφέρονται στο ίδιο αρχείο, το αντίγραφο θα πρέπει να έχει κόμβους
τ1 και τ2 οι οποίοι όμως θα αναφέρονται στα ίδια μπλοκς αρχείου.


΄Εχετε την δυνατότητα να προσθέσετε οποιαδήποτε άλλη σημαία κρίνετε απαραίτητη.
Στο τέλος το πρόγραμμα σας θα πρέπει να παρέχει κάποια βασικά χαρακτηριστικά όσον αφορά την συμπεριφορά
του όπως:
1. αριθμό οντοτήτων (αρχεία, καταλόγους και πιθανώς συνδέσμους) που το πρόγραμμα έχει «δει» στην
συγκεκριμένη εκτέλεσή του,
2. αριθμό από τις παραπάνω οντότητες που τελικά αντιγράφησαν,
3. των αριθμό των bytes που αντιγράφησαν συνολικά, χρόνος που απαιτήθηκε για την εργασία του προγράμματος και το ρυθμό με τον οποίο γράφτηκαν τα παραπάνω bytes στο κατάλογου προορισμού.
