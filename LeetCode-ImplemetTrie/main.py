class Trie:
    def __init__(self):
        self.root = {}

    def insert(self, word: str) -> None:
        if self.search(word) == True:
            return
        if word == "":
            return
        if word in self.root:
            self.root[word][1] = True
            return
        word_prefix_longest_in_stage = 0
        for i in range(len(word), 0, -1):
            prefix_of_word = word[:i]
            for key in self.root.keys():
                if key == prefix_of_word:
                    self.root[key][0].insert(word[i:])
                    return
                if key.startswith(prefix_of_word):
                    # We need to divide the tree!
                    word_suffix = word[i:]
                    key_suffix = key[i:]
                    moved_tree = self.root[key][0]
                    is_key_a_word = self.root[key][1]
                    del self.root[key]
                    self.root[prefix_of_word] = [Trie(), prefix_of_word == word]
                    if prefix_of_word != word:
                        self.root[prefix_of_word][0].root[word_suffix] = [Trie(), True]
                    self.root[prefix_of_word][0].root[key_suffix] = [moved_tree, is_key_a_word]
                    return
        # If we got here no key has any mutual part with word
        self.root[word] = [Trie(), True]

    def search(self, word: str) -> bool:
        if word == "":
            return True
        if word in self.root:
            return self.root[word][1]
        for i in range(len(word), 0, -1):
            prefix_of_word = word[:i]
            if prefix_of_word in self.root:
                return self.root[prefix_of_word][0].search(word[i:])
        return False

    def startsWith(self, prefix: str) -> bool:
        if prefix == "":
            return True
        if prefix in self.root:
            return True
        for key in self.root.keys():
            if key.startswith(prefix):
                return True
        for i in range(len(prefix), 0, -1):
            prefix_of_word = prefix[:i]
            if prefix_of_word in self.root:
                return self.root[prefix_of_word][0].startsWith(prefix[i:])
        return False

    def printTree(self, prefix: str) -> None:
        for key in self.root.keys():
            if self.root[key][1] == True:
                print(f"{prefix} -> {key}")
            self.root[key][0].printTree(prefix + " -> " + key)

# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)


# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)

def main():
    a = ["Trie","insert","insert","insert","insert","insert","insert","search","search","search","search","search","search","search","search","search","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith","startsWith"]
    b = [[],["app"],["apple"],["beer"],["add"],["jam"],["rental"],["apps"],["app"],["ad"],["applepie"],["rest"],["jan"],["rent"],["beer"],["jam"],["apps"],["app"],["ad"],["applepie"],["rest"],["jan"],["rent"],["beer"],["jam"]]

    tree = Trie()
    print("null")
    for i in range(1,len(a)):
        print(f"{a[i]} -> {b[i]}")
        if a[i] == "insert":
            tree.insert(b[i][0])
            print("null")
        elif a[i] == "search":
            print(tree.search(b[i][0]))
        elif a[i] == "startsWith":
            print(tree.startsWith(b[i][0]))
        tree.printTree("")

if __name__ == '__main__':
    main()