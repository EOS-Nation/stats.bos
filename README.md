# BOS Statistics

Calculates BP votes benchmark deployed as a smart contract on BOS (`stats.bos`).

## Javascript example

```typescript
let bp_votes = 0;
let bp_producers_votes = 0;
let bp_proxy_votes = 0;

// Accumulate staked BOS for voters that have voted for BP's
for (const voter of voters) {
    const staked = Number(voter.staked);

    // Voter must vote for BP or proxy
    if (!voter.producers.length && !voter.proxy) continue;

    // Total BP Votes
    bp_votes += staked;

    // Voters voting for BP's
    if (voter.producers.length) bp_producers_votes += staked;

    // Proxies voting for BP's
    if (voter.proxy) bp_proxy_votes += staked;
}
```